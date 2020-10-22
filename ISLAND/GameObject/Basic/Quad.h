#pragma once

class Quad : public Transform
{
	typedef VertexUV VertexType;
private:
	Mesh* mesh;
	Material* material;

	RasterizerState* rasterizerState[2];
	BlendState* blendState[2];

public:
	Quad();
	~Quad();

	void Update();
	void Render();
	void PostRender();

	// DiffuseMap에 넣어버리자
	void SetTexure(wstring file= L"");

private:
	void Create();
};