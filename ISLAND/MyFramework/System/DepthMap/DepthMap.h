#pragma once

class DepthMap
{
private:
	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	// 확인용
	class Render2D* depthTexture;

	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;

public:
	DepthMap();
	~DepthMap();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	// TODO: 그림자 만들 때 사용하자!!
	void SetViewProjection();
};