#include "Framework.h"

Quad::Quad()
{
	Create();

	material = new Material(L"UV");

	rasterizerState[0] = new RasterizerState();
	rasterizerState[1] = new RasterizerState();
	rasterizerState[1]->FillMode(D3D11_FILL_WIREFRAME);

	blendState[0] = new BlendState();
	blendState[1] = new BlendState();
	blendState[1]->Alpha(true);

	UpdateWorld();
}

Quad::~Quad()
{
	delete mesh;
	delete material;

	delete rasterizerState[0];
	delete rasterizerState[1];
	delete blendState[0];
	delete blendState[1];
}

void Quad::Update()
{
	UpdateWorld();
}

void Quad::Render()
{
	mesh->Set();
	SetWorldBuffer();
	material->Set();

	blendState[1]->SetState();
	//rasterizerState[1]->SetState();
	DC->DrawIndexed(mesh->GetIndexCount(), 0, 0);
	//rasterizerState[0]->SetState();
	blendState[0]->SetState();
}

void Quad::PostRender()
{
	if (ImGui::Button("Load", ImVec2(100, 40)))
		SetTexure();

}

void Quad::SetTexure(wstring file)
{
	if (file == L"")
	{
		function<void(wstring)> func = bind(&Quad::SetTexure, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L".\\", func, hWnd);
	}
	else
		material->SetDiffuseMap(file);
}

void Quad::Create()
{
	vector<VertexType> vertices(4);
	vector<UINT> indices(6);

	vertices[0].position = { -0.5f, +0.5f, 0 };
	vertices[1].position = { +0.5f, +0.5f, 0 };
	vertices[2].position = { -0.5f, -0.5f, 0 };
	vertices[3].position = { +0.5f, -0.5f, 0 };

	vertices[0].uv = { 0, 0 };
	vertices[1].uv = { 1, 0 };
	vertices[2].uv = { 0, 1 };
	vertices[3].uv = { 1, 1 };
	
	indices = {
		0, 1, 2,
		2, 1, 3
	};

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
