#include "Framework.h"

Refraction::Refraction()
{
	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();

	targetTexture = new Render2D(L"UV");
	targetTexture->SetSRV(renderTarget->GetSRV());
	// 균등 스케일이 연산이 더 빠름
	targetTexture->scale = { 300, 300, 300 };
	targetTexture->position = { 450, 150, 0 };
}

Refraction::~Refraction()
{
	delete renderTarget;
	delete depthStencil;
	delete targetTexture;
}

void Refraction::Update()
{
	targetTexture->Update();
}

void Refraction::PreRender()
{
	renderTarget->Set(depthStencil);
}

void Refraction::Render()
{
	DC->PSSetShaderResources(11, 1, &renderTarget->GetSRV());
}

void Refraction::PostRender()
{
	targetTexture->Render();
}