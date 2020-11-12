#pragma once

class Refraction
{
private:
	RenderTarget* renderTarget;
	DepthStencil* depthStencil;

	class Render2D* targetTexture;

public:
	Refraction();
	~Refraction();

	void Update();

	void PreRender();
	void Render();
	void PostRender();
};