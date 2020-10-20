#include "Framework.h"

Environment* Environment::instance = nullptr;

Environment::Environment()
{
    CreateViewort();
    CreatePerspective();
}

Environment::~Environment()
{
    delete viewBuffer;
    delete projectionBuffer;
}

void Environment::CreateViewort()
{
    D3D11_VIEWPORT vp;
    vp.Width = WIN_WIDTH;
    vp.Height = WIN_HEIGHT;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    DC->RSSetViewports(1, &vp);
}

void Environment::CreatePerspective()
{
    viewBuffer = new MatrixBuffer();
    projectionBuffer = new MatrixBuffer();

    XMVECTOR eye = XMVectorSet(3, 3, -3, 0);
    XMVECTOR focus = XMVectorSet(0, 0, 0, 0);
    XMVECTOR up = XMVectorSet(0, 1, 0, 0);

    XMMATRIX view = XMMatrixLookAtLH(eye, focus, up);

    viewBuffer->Set(view);

    XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2,
        WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    projectionBuffer->Set(projection);
}
