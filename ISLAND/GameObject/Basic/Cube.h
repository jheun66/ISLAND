#pragma once

// TODO : Test용임 게임에 사용 x, 나중에 지우기
class Cube
{
	struct VertexColor
	{
		XMFLOAT3 position;
		XMFLOAT4 color;

		VertexColor() :position(0, 0, 0), color(1, 1, 1, 1)
		{

		}
	};

private:
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	XMFLOAT3 pivot;

	XMMATRIX world;
	XMMATRIX* parent;

	VertexShader* vertexShader;
	PixelShader* pixelShader;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

	MatrixBuffer* worldBuffer;

	bool isControl = false;

public:
	Cube();
	~Cube();

	void Update();
	void Render();

	void Create();

	XMMATRIX* GetWorld() { return &world; }
	void SetPos(XMFLOAT3 value) { position = value; }
	void SetControl(bool value) { isControl = value; }
	void SetParent(XMMATRIX* value) { parent = value; }
};