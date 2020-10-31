#include "Framework.h"

Environment* Environment::instance = nullptr;

Environment::Environment()
{
    CreateViewort();
    CreatePerspective();
    CreateSamplerState();

    mainCamera = new FreeCamera();

    lights = new LightBuffer();

    Light light;
    light.type = Light::DIRECTION;
    //lightInfo.position = { 0, 30, -10 };
    light.direction = { 0,-1, 1 };

    lights->Add(light);

}

Environment::~Environment()
{
    delete projectionBuffer;
    delete samplerState;

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

    ImGui::Text("LightInfo");
    ImGui::ColorEdit4("Ambient", (float*)&lights->data.ambient);
    ImGui::ColorEdit4("AmbientCeil", (float*)&lights->data.ambientCeil);

    if (ImGui::Button("AddLight"))
    {
        lights->Add();
    }
    for (UINT i = 0; i < lights->data.lightCount; i++)
    {
        string menuName = "Light" + to_string(i);
        if (ImGui::BeginMenu(menuName.c_str()))
        {
            ImGui::SliderInt("Type", (int*)&lights->data.lights[i].type, 0, 3);
            ImGui::SliderFloat3("Position", (float*)&lights->data.lights[i].position, -100, 100);
            ImGui::SliderFloat("Range", &lights->data.lights[i].range, 0, 1000);
            ImGui::ColorEdit4("Color", (float*)&lights->data.lights[i].color);
            ImGui::SliderFloat3("Direction", (float*)&lights->data.lights[i].direction, -1, 1);
            ImGui::SliderFloat("Outer", &lights->data.lights[i].outer, 0, 180);
            // 90 넘으면 반전
            ImGui::SliderFloat("Inner", &lights->data.lights[i].inner, 0, 89);
            ImGui::SliderFloat("Length", &lights->data.lights[i].length, 0, 100);
            ImGui::Checkbox("Active", (bool*)&lights->data.lights[i].active);

            ImGui::EndMenu();
        }
    }
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

    projection = XMMatrixPerspectiveFovLH(XM_PIDIV4,
        WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);

    projectionBuffer->Set(projection);
}

void Environment::CreateSamplerState()
{
    samplerState = new SamplerState();
    //samplerState->Address(D3D11_TEXTURE_ADDRESS_CLAMP);
    samplerState->SetState();
}