#include "Framework.h"

DepthMap::DepthMap()
	:viewBuffer(nullptr), projectionBuffer(nullptr)
{
	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();

	depthTexture = new Render2D(L"UV");
	depthTexture->SetSRV(renderTarget->GetSRV());
	// �յ� �������� ������ �� ����
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

	// �ٲ��ְ� ������, ������ ���� view, projection ���
	//SetViewProjection()
}

void DepthMap::Render()
{
	// ������ 12���� ������( low poly water���� ���)
	DC->PSSetShaderResources(12, 1, &renderTarget->GetSRV());
}

void DepthMap::PostRender()
{
	depthTexture->Render();
}

void DepthMap::SetViewProjection()
{
	// �׸��ڸ� ���� ��, ���� ��ġ���� �� ������ view, projection �������ֱ�
}
