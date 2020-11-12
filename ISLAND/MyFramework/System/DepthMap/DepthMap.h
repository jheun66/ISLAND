#pragma once

class DepthMap
{
private:
	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	// Ȯ�ο�
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

	// TODO: �׸��� ���� �� �������!!
	void SetViewProjection();
};