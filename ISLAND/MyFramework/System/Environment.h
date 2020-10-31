#pragma once

// TODO : SamplerState
class MatrixBuffer;
class LightBuffer;

class Environment
{
private:
	XMMATRIX projection;
	MatrixBuffer* projectionBuffer;
	LightBuffer* lights;

	Camera* mainCamera;

	SamplerState* samplerState;

	D3D11_VIEWPORT viewport;

	static Environment* instance;
	Environment();
	~Environment();
public:
	static Environment* Get() { return instance; }
	static void Create() { instance = new Environment(); }
	static void Delete() { delete instance; }

	Camera* MainCamera() { return mainCamera; }
	MatrixBuffer* GetProjectionBuffer() { return projectionBuffer; }
	LightBuffer* GetLight() { return lights; }
	XMMATRIX GetProjection() { return projection; }

	void ChangeCameraMode(bool isFollowCamera);

	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void PostRender();
private:
	void CreateViewort();
	void CreatePerspective();
	void CreateSamplerState();
};