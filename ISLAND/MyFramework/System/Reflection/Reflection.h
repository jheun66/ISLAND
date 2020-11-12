#pragma once

class Reflection
{
private:
	float waterHeight = 0.0f;

	FreeCamera* camera;

	MatrixBuffer* reflectionBuffer;

	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	class Render2D* targetTexture;

public:
	Reflection();
	~Reflection();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void SetWaterHeight(float height) { waterHeight = height; }
};