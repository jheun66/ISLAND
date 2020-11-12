#include "Framework.h"

LowPolyWater::LowPolyWater(float width, float height)
	:width(width), height(height)
{
	material = new Material(L"LowPolyWater");

	reflection = new Reflection();
	refraction = new Refraction();
	depthMap = new DepthMap();

	CreateMesh();
	mesh = new Mesh(alignedVertices.data(), sizeof(VertexType), alignedVertices.size(),
		indices.data(), indices.size());

	nearFarBuffer = new NearFarBuffer();
	waterOption = new WaterOptionBuffer();
	reflection->SetWaterHeight(waterOption->data.waterHeight);

	timeBuffer = new TimeBuffer();

	rs[0] = new RasterizerState();
	rs[1] = new RasterizerState();
	rs[1]->FillMode(D3D11_FILL_WIREFRAME);
}

LowPolyWater::~LowPolyWater()
{
	delete material;
	delete mesh;

	delete reflection;
	delete refraction;
	delete depthMap;

	delete nearFarBuffer;
	delete waterOption;
	delete timeBuffer;

	delete rs[0];
	delete rs[1];
}

void LowPolyWater::Update()
{
	timeBuffer->data.time += DELTA;

	reflection->SetWaterHeight(waterOption->data.waterHeight);
	reflection->Update();
	refraction->Update();
	depthMap->Update();

	UpdateWorld();
}

void LowPolyWater::SetDepthMap()
{
	depthMap->PreRender();
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
	waterOption->SetVSBuffer(11);
	nearFarBuffer->SetPSBuffer(10);

	reflection->Render();
	refraction->Render();
	depthMap->Render();

	material->Set();

	if (viewWire)
		rs[1]->SetState();
	DC->DrawIndexed(indices.size(), 0, 0);
	rs[0]->SetState();
}

void LowPolyWater::PostRender()
{
	//depthMap->PostRender();
	//refraction->PostRender();
	//reflection->PostRender();
	ImGui::Begin("Water", 0, ImGuiWindowFlags_AlwaysAutoResize);
	{
		ImGui::SliderFloat("Water Height", &waterOption->data.waterHeight, -1.0f, 40.0f);
		ImGui::SliderFloat("Wave Length", &waterOption->data.waveLength, 1.0f, 10.0f);
		ImGui::SliderFloat("Wave Amplitude", &waterOption->data.waveAmplitude, 0.0f, 1.0f);

		ImGui::SliderFloat("Reflection Offset", &reflectionOffset, -40.0f, 0.0f);
		ImGui::SliderFloat("Refraction Offset", &refractionOffset, -50.0f, 50.0f);

		if (ImGui::Button("View Wire", ImVec2(120, 40)))
		{
			viewWire = !viewWire;
		}

		//ImGui::SliderFloat("Near Plane", &nearFarBuffer->data.nearPlane, -1.0f, 10.0f);
		//ImGui::SliderFloat("Far Plane", &nearFarBuffer->data.farPlane, 100.0f, 1100.0f);
	}
	ImGui::End();
}

void LowPolyWater::CreateMesh()
{
	vertices.resize(width * height);
	for (UINT i = 0; i < height; i++)
	{
		for (UINT j = 0; j < width; j++)
		{
			vertices[i * width + j].position = { (float)j, 0.0f, (float)i };
		}
	}

	UINT index = 0;
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			VertexType four[4] = { vertices[width * z + x], vertices[width * (z + 1) + x],
			vertices[width * z + x + 1], vertices[width * (z + 1) + x + 1] };

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
	vertex.indicators.y = four[vertex1].position.z - vertex.position.z;
	vertex.indicators.z = four[vertex2].position.x - vertex.position.x;
	vertex.indicators.w = four[vertex2].position.z - vertex.position.z;
	return vertex;
}
