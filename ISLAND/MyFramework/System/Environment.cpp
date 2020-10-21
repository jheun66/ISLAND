#include "Framework.h"

Environment* Environment::instance = nullptr;

Environment::Environment()
{
    CreateViewort();
    CreatePerspective();
    //CreateSamplerState();

    mainCamera = new FreeCamera();
}

Environment::~Environment()
{
    delete projectionBuffer;


    delete mainCamera;
}

void Environment::ChangeCameraMode(bool isFollowCamera)
{
    delete mainCamera;

    if (isFollowCamera)
        mainCamera = new FollowCamera();
    else
        mainCamera = new FreeCamera();
}

void Environment::SetViewport(UINT width, UINT height)
{
    viewport.Width = width;
    viewport.Height = height;

    DC->RSSetViewports(1, &viewport);
}

void Environment::PostRender()
{
    mainCamera->PostRender();
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
    projectionBuffer = new MatrixBuffer();

    projection = XMMatrixPerspectiveFovLH(XM_PIDIV2,
        WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    projectionBuffer->Set(projection);
}
