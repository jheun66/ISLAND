#include "Framework.h"

Terrain::Terrain(UINT width, UINT height)
	:width(width), height(height)
{
	CreateTerrain();
	CreateNormal();
	CreateTangent();
	// compute, alphaMap 은 나중에 추가
	CreateCompute(); // 아직 구현 x


	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(),
		indices.data(), indices.size());

	material = new Material(L"UV");

	UpdateWorld();

	rs[0] = new RasterizerState();
	rs[1] = new RasterizerState();
	rs[1]->FillMode(D3D11_FILL_WIREFRAME);

}

Terrain::~Terrain()
{
	delete mesh;
	delete material;
}

void Terrain::Render()
{
	mesh->Set();
	SetWorldBuffer();
	material->Set();

	rs[1]->SetState();
	DC->DrawIndexed(indices.size(), 0, 0);
	rs[0]->SetState();

}

void Terrain::Update()
{
	
}

void Terrain::PostRender()
{
	if (ImGui::Button("Load HeightMap", ImVec2(120, 40)))
		LoadHeightMap(L"");

	if (ImGui::Button("Save HeightMap", ImVec2(120, 40)))
		SaveHeightMap(L"");

	if (ImGui::Button("Generate Noise", ImVec2(120, 40)))
		GenerateNoise();

}

void Terrain::SaveHeightMap(wstring path)
{
	if (path == L"")
	{
		function<void(wstring)> func = bind(&Terrain::SaveHeightMap, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::ImageFilter, L".\\", func, hWnd);
	}
	else
	{
		UINT size = width * height * 4;
		uint8_t* pixels = new uint8_t[size];

		for (UINT i = 0; i < size / 4; i++)
		{
			float y = (vertices[i].position.y) / 60.0f * 255.0f;

			for (UINT j = 0; j < 3; j++)
			{
				pixels[i * 4 + j] = y;
			}

			pixels[i * 4 + 3] = 255;
		}

		Image image;

		image.width = width;
		image.height = height;
		image.pixels = pixels;
		image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
		image.rowPitch = (size_t)width * 4;

		image.slicePitch = image.width * image.height * 4;

		SaveToWICFile(image, WIC_FLAGS_FORCE_RGB, GetWICCodec(WIC_CODEC_PNG), path.c_str());
	}
}

void Terrain::LoadHeightMap(wstring path)
{
	if (path == L"")
	{
		function<void(wstring)> func = bind(&Terrain::LoadHeightMap, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L".\\", func, hWnd);
	}
	else
	{
		heightMap = Texture::Add(path);
		vector<Float4> pixels = heightMap->ReadPixels();

		for (UINT i = 0; i < pixels.size(); i++)
		{
			vertices[i].position.y = 0;
			vertices[i].position.y += pixels[i].x * 60.0f;
		}

		CreateNormal();
		CreateTangent();
		CreateCompute();

		mesh->UpdateVertex(vertices.data(), vertices.size());
	}	
}

void Terrain::CreateTerrain()
{
	vertices.resize((size_t)height * width);

	UINT index = 0;
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			VertexType vertex;
			vertex.position = Float3(x, 0, z);
			vertex.uv = Float2(x / (float)width, 1.0f - (z / (float)height));

			vertices[index++] = vertex;
		}
	}

	for (UINT z = 0; z < height-1; z++)
	{
		for (UINT x = 0; x < width-1; x++)
		{
			indices.emplace_back(width * z + x);
			indices.emplace_back(width * (z + 1) + x);
			indices.emplace_back(width * (z + 1) + x + 1);
			indices.emplace_back(width * z + x);
			indices.emplace_back(width * (z + 1) + x + 1);
			indices.emplace_back(width * z + x + 1);
		}
	}

}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v0 = vertices[index0].position;
		Vector3 v1 = vertices[index1].position;
		Vector3 v2 = vertices[index2].position;

		Vector3 A = v1 - v0;
		Vector3 B = v2 - v0;

		Vector3 normal = Vector3::Cross(A, B).Normal();

		vertices[index0].normal = (vertices[index0].normal + normal).Normal();
		vertices[index1].normal = (vertices[index1].normal + normal).Normal();
		vertices[index2].normal = (vertices[index2].normal + normal).Normal();
	}
}

void Terrain::CreateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		VertexType vertex0 = vertices[index0];
		VertexType vertex1 = vertices[index1];
		VertexType vertex2 = vertices[index2];

		Vector3 p0 = vertex0.position;
		Vector3 p1 = vertex1.position;
		Vector3 p2 = vertex2.position;

		XMFLOAT2 uv0 = vertex0.uv;
		XMFLOAT2 uv1 = vertex1.uv;
		XMFLOAT2 uv2 = vertex2.uv;

		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		float u0 = uv1.x - uv0.x;
		float u1 = uv2.x - uv0.x;
		float v0 = uv1.y - uv0.y;
		float v1 = uv2.y - uv0.y;

		float d = 1.0f / (u0 * v1 - v0 * u1);

		Vector3 tangent;
		tangent = (v1 * e0 - v0 * e1) * d;

		vertices[index0].tangent = tangent + vertices[index0].tangent;
		vertices[index1].tangent = tangent + vertices[index1].tangent;
		vertices[index2].tangent = tangent + vertices[index2].tangent;

	}

	for (VertexType& vertex : vertices)
	{
		Vector3 t = vertex.tangent;
		Vector3 n = vertex.normal;

		Vector3 temp = (t - n * Vector3::Dot(n, t)).Normal();

		vertex.tangent = temp;
	}
}

void Terrain::CreateCompute()
{
}

void Terrain::GenerateNoise()
{
	// 초기화
	for (auto& w : noise)
	{
		w.clear();
	}
	noise.clear();

	noise.resize(height, vector<float>(width));


	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			noise[i][j] = (rand() % 32768) / 32768.0f;
		}
	}

	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			UINT index = i * height + j;

			vertices[index].position.y = 0.0f;
			vertices[index].position.y += Turbulence(j, i, 64) * 60.0f;
		}
	}

	CreateNormal();
	CreateTangent();
	CreateCompute();

	mesh->UpdateVertex(vertices.data(), vertices.size());
}

float Terrain::SmoothNoise(float x, float y)
{
	float fractX = x - int(x);
	float fractY = y - int(y);

	int x1 = (int(x) + width) % width;
	int y1 = (int(y) + height) % height;

	int x2 = (int(x1) + width - 1) % width;
	int y2 = (int(y1) + height - 1) % height;

	float value = 0.0f;
	value += fractX * fractY * noise[y1][x1];
	value += (1 - fractX) * fractY * noise[y1][x2];
	value += fractX * (1 - fractY) * noise[y2][x1];
	value += (1 - fractX) * (1 - fractY) * noise[y2][x2];

	return value;
}

float Terrain::Turbulence(float x, float y, float size)
{
	float value = 0.0f, initialSize = size;

	while (size >= 1)
	{
		value += SmoothNoise(x / size, y / size) * size;
		size /= 2.0f;
	}
	return (0.5f * value / initialSize);
}
