#include "Framework.h"

Terrain::Terrain(UINT width, UINT height)
	:width(width), height(height), maxH(60.0f)
{
	// terrain color
	colorSpread = 0.45f;
	halfSpread = colorSpread / 2;
	terrain_cols = { Float4(201 / 255.0f, 178 / 255.0f, 99 / 255.0f, 1),
	Float4(135 / 255.0f, 184 / 255.0f, 82 / 255.0f, 1),
	Float4(80 / 255.0f, 171 / 255.0f, 93 / 255.0f, 1),
	Float4(120 / 255.0f, 120 / 255.0f, 120 / 255.0f, 1),
	Float4(200 / 255.0f, 200 / 255.0f, 210 / 255.0f, 1) };
	part = 1.0f / (terrain_cols.size() - 1);

	CreateTerrain();
	CreateColor();
	AlignVertices();
	CreateNormal();
	CreateCompute(); // 아직 구현 x


	mesh = new Mesh(alignedVertices.data(), sizeof(VertexType), alignedVertices.size(),
		indices.data(), indices.size());

	material = new Material(L"Terrain");

	UpdateWorld();

	rs[0] = new RasterizerState();
	rs[1] = new RasterizerState();
	rs[1]->FillMode(D3D11_FILL_WIREFRAME);

}

Terrain::~Terrain()
{
	delete mesh;
	delete material;

	delete rs[0];
	delete rs[1];
}

void Terrain::Render()
{
	mesh->Set();
	SetWorldBuffer();
	material->Set();

	if(viewWire)
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

	if (ImGui::Button("Adjust Gradient", ImVec2(120, 40)))
		AdjustGradient(L"");

	if (ImGui::Button("View Wire", ImVec2(120, 40)))
	{
		viewWire = !viewWire;
	}

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
			float y = (vertices[i].position.y) / maxH * 255.0f;

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
			vertices[i].position.y += pixels[i].x * maxH;
		}

		CreateColor();
		AlignVertices();
		CreateNormal();
		CreateCompute();

		mesh->UpdateVertex(alignedVertices.data(), alignedVertices.size());
	}	
}

void Terrain::AdjustGradient(wstring path)
{
	if (path == L"")
	{
		function<void(wstring)> func = bind(&Terrain::AdjustGradient, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L".\\", func, hWnd);
	}
	else
	{
		gradientMap = Texture::Add(path);
		vector<Float4> pixels = gradientMap->ReadPixels();

		for (UINT i = 0; i < pixels.size(); i++)
		{
			vertices[i].position.y -= pixels[i].x * maxH;
			if (vertices[i].position.y < 0)
				vertices[i].position.y = 0.0f;
		}

		CreateColor();
		AlignVertices();
		CreateNormal();
		CreateCompute();

		mesh->UpdateVertex(alignedVertices.data(), alignedVertices.size());
	}
}

void Terrain::CreateColor()
{
	UINT index = 0;
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			vertices[index].color = calculateColor(vertices[index].position.y, maxH);
			index++;
		}
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

	index = 0;
	for (UINT z = 0; z < height-1; z++)
	{
		for (UINT x = 0; x < width-1; x++)
		{
			if (!((x % 2) ^ (z % 2)))
			{
				alignedVertices.push_back(vertices[width * z + x]);
				alignedVertices.push_back(vertices[width * (z + 1) + x]);
				alignedVertices.push_back(vertices[width * (z + 1) + x + 1]);
				alignedVertices.push_back(vertices[width * z + x]);
				alignedVertices.push_back(vertices[width * (z + 1) + x + 1]);
				alignedVertices.push_back(vertices[width * z + x + 1]);
			}
			else
			{
				alignedVertices.push_back(vertices[width * z + x]);
				alignedVertices.push_back(vertices[width * (z + 1) + x]);
				alignedVertices.push_back(vertices[width * z + x + 1]);
				alignedVertices.push_back(vertices[width * (z + 1) + x]);
				alignedVertices.push_back(vertices[width * (z + 1) + x + 1]);
				alignedVertices.push_back(vertices[width * z + x + 1]);
			}

			for (int i = 0; i < 6; i++)
			{
				indices.emplace_back(index++);
			}
		}
	}

}

void Terrain::AlignVertices()
{

	UINT index = 0;
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			if (!((x % 2)^(z % 2)))
			{
				alignedVertices[index++] = vertices[width * z + x];
				alignedVertices[index++] = vertices[width * (z + 1) + x];
				alignedVertices[index++] = vertices[width * (z + 1) + x + 1];

				alignedVertices[index++] = vertices[width * z + x];
				alignedVertices[index++] = vertices[width * (z + 1) + x + 1];
				alignedVertices[index++] = vertices[width * z + x + 1];
			}
			else
			{
				alignedVertices[index++] = vertices[width * z + x];
				alignedVertices[index++] = vertices[width * (z + 1) + x];
				alignedVertices[index++] = vertices[width * z + x + 1];

				alignedVertices[index++] = vertices[width * (z + 1) + x];
				alignedVertices[index++] = vertices[width * (z + 1) + x + 1];
				alignedVertices[index++] = vertices[width * z + x + 1];
			}
		}
	}


}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = i * 3 + 0;
		UINT index1 = i * 3 + 1;
		UINT index2 = i * 3 + 2;

		Vector3 v0 = alignedVertices[index0].position;
		Vector3 v1 = alignedVertices[index1].position;
		Vector3 v2 = alignedVertices[index2].position;

		Vector3 A = v1 - v0;
		Vector3 B = v2 - v0;

		Vector3 normal = Vector3::Cross(A, B).Normal();

		alignedVertices[index0].normal = normal;
		alignedVertices[index1].normal = normal;
		alignedVertices[index2].normal = normal;
	}
}

void Terrain::CreateCompute()
{
}

Float4 Terrain::calculateColor(float height, float amplitude)
{
	Float4 returnColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	height = 2 * height - amplitude;
	float value = (height + amplitude) / (amplitude * 2);

	value = GameMath::Clamp((value - halfSpread) * (1.0f / colorSpread), 0.0f, 0.9999f);
	int firstBiome = (int)floor(value / part);
	float blend = (value - (firstBiome * part)) / part;
	returnColor.x = LERP(terrain_cols[firstBiome].x, terrain_cols[firstBiome + 1].x, blend);
	returnColor.y = LERP(terrain_cols[firstBiome].y, terrain_cols[firstBiome + 1].y, blend);
	returnColor.z = LERP(terrain_cols[firstBiome].z, terrain_cols[firstBiome + 1].z, blend);
	return returnColor;
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
			vertices[index].position.y += Turbulence(j, i, 64) * maxH;
		}
	}

	CreateColor();
	AlignVertices();
	CreateNormal();
	CreateCompute();

	mesh->UpdateVertex(alignedVertices.data(), alignedVertices.size());
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
