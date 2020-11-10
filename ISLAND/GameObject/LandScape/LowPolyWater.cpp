#include "Framework.h"

LowPolyWater::LowPolyWater(float width, float hieght)
	:width(width), height(height)
{
	material = new Material(L"LowPolyWater");

	buffer = new WaterBuffer();

	reflection = new Reflection(this);
	refraction = new Refraction(L"Textures/Wave.dds");

	CreateMesh();
	mesh = new Mesh(alignedVertices.data(), sizeof(VertexType), alignedVertices.size(),
		indices.data(), indices.size());

	timeBuffer = new TimeBuffer();

	blendState[0] = new BlendState();
	blendState[1] = new BlendState();
	blendState[1]->Alpha(true);

	rasterizerState[0] = new RasterizerState();
	rasterizerState[1] = new RasterizerState();
	rasterizerState[0]->FillMode(D3D11_FILL_WIREFRAME);
}

LowPolyWater::~LowPolyWater()
{
	delete material;
	delete mesh;

	delete buffer;

	delete reflection;
	delete refraction;

	delete timeBuffer;

	delete blendState[0];
	delete blendState[1];

	delete rasterizerState[0];
	delete rasterizerState[1];
}

void LowPolyWater::Update()
{
	timeBuffer->data.time += DELTA;

	buffer->data.waveTranslation += buffer->data.waveSpeed * DELTA;
	if (buffer->data.waveTranslation > 1.0f)
		buffer->data.waveTranslation -= 1.0f;

	reflection->Update();
	refraction->Update();

	UpdateWorld();
}

void LowPolyWater::SetReflection()
{
	reflection->PreRender();
}

void LowPolyWater::SetRefraction()
{
	refraction->PreRender();
}

void LowPolyWater::Render()
{
	mesh->Set();

	SetWorldBuffer();

	timeBuffer->SetVSBuffer(9);
	buffer->SetPSBuffer(10);

	reflection->Render();
	refraction->Render();

	material->Set();

	rasterizerState[1]->SetState();
	blendState[1]->SetState();
	DC->DrawIndexed(indices.size(), 0, 0);
	blendState[0]->SetState();
	rasterizerState[0]->SetState();
}

void LowPolyWater::PostRender()
{
	ImGui::Text("Water Option");
	ImGui::ColorEdit4("Color", (float*)&buffer->data.color);
	ImGui::SliderFloat("WaveScale", &buffer->data.waveScale, 0.0f, 10.0f);
	ImGui::SliderFloat("WaveSpeed", &buffer->data.waveSpeed, 0.0f, 1.0f);
	ImGui::SliderFloat("Alpha", &buffer->data.alpha, 0.0f, 1.0f);
	ImGui::SliderFloat("Shininess", &buffer->data.shininess, 0.0f, 50.0f);
}

void LowPolyWater::CreateMesh()
{
	vertices.resize(width * height);
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			vertices[i * height + j].position = { (float)i, 0.0f, (float)j };
		}
	}

	UINT index = 0;
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			VertexType four[4] = { vertices[width * z + x],vertices[width * (z + 1) + x],
			vertices[width * z + x + 1],vertices[width * (z + 1) + x + 1] };

			if (!((x % 2) ^ (z % 2)))
			{
				alignedVertices.emplace_back(CalcIndicators(four, 0, 1, 3));
				alignedVertices.emplace_back(CalcIndicators(four, 1, 3, 0));
				alignedVertices.emplace_back(CalcIndicators(four, 3, 0, 1));

				alignedVertices.emplace_back(CalcIndicators(four, 0, 3, 2));
				alignedVertices.emplace_back(CalcIndicators(four, 3, 2, 0));
				alignedVertices.emplace_back(CalcIndicators(four, 2, 0, 3));
			}
			else
			{
				alignedVertices.emplace_back(CalcIndicators(four, 0, 1, 2));
				alignedVertices.emplace_back(CalcIndicators(four, 1, 2, 0));
				alignedVertices.emplace_back(CalcIndicators(four, 2, 0, 1));

				alignedVertices.emplace_back(CalcIndicators(four, 1, 3, 2));
				alignedVertices.emplace_back(CalcIndicators(four, 3, 2, 1));
				alignedVertices.emplace_back(CalcIndicators(four, 2, 1, 3));
			}

			for (int i = 0; i < 6; i++)
			{
				indices.emplace_back(index++);
			}
		}
	}
}

VertexLowPolyWater LowPolyWater::CalcIndicators(VertexType* four, UINT curVertex, UINT vertex1, UINT vertex2)
{
	VertexType vertex;
	vertex.position = four[curVertex].position;
	vertex.indicators.x = four[vertex1].position.x - vertex.position.x;
	vertex.indicators.y = four[vertex1].position.y - vertex.position.y;
	vertex.indicators.z = four[vertex2].position.x - vertex.position.x;
	vertex.indicators.w = four[vertex2].position.y - vertex.position.y;
	return vertex;
}
