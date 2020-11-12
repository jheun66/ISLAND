#include "Framework.h"

DepthMap::DepthMap()
	:viewBuffer(nullptr), projectionBuffer(nullptr)
{
	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();

	depthTexture = new Render2D(L"UV");
	depthTexture->SetSRV(renderTarget->GetSRV());
	// 균등 스케일이 연산이 더 빠름
	depthTexture->scale = { 300, 300, 300 };
	depthTexture->position = { 150, 150, 0 };
}

DepthMap::~DepthMap()
{
	delete renderTarget;
	delete depthStencil;

	delete depthTexture;

	if(viewBuffer != nullptr)
		delete viewBuffer;
	if (projectionBuffer != nullptr)
		delete projectionBuffer;
}

void DepthMap::Update()
{
	depthTexture->Update();
}

void DepthMap::PreRender()
{
	renderTarget->Set(depthStencil);

	// 바꿔주고 싶으면, 지금은 기존 view, projection 사용
	//SetViewProjection()
}

void DepthMap::Render()
{
	// 지금은 12번에 세팅함( low poly water에서 사용)
	DC->PSSetShaderResources(12, 1, &renderTarget->GetSRV());
}

void DepthMap::PostRender()
{
	depthTexture->Render();
}

void DepthMap::SetViewProjection()
{
	// 그림자를 만들 때, 빛의 위치에서 본 것으로 view, projection 변경해주기
}
