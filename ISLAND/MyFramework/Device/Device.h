#pragma once

class Device
{
private:
	HWND hWnd;

	// direct는 하드에 직접 접근해 처리하는데 device는 cpu, context는 gpu를 대행해 처리한다.
	ID3D11Device* device;                       // CPU, 리소스 할당
	ID3D11DeviceContext* deviceContext;         // GPU, 렌더링

												// View가 붙으면 GPU 관련
	IDXGISwapChain* swapChain;                  // 더블 버퍼 관리
	ID3D11RenderTargetView* renderTargetView;   // 백 버퍼

	static Device* instance;

	Device(HWND hWnd);
	~Device();


public:
	static Device* Get() { return instance; }
	static void Create(HWND hWnd) { instance = new Device(hWnd); }
	static void Delete() { delete instance; }

	void CreateDevcieAndSwapChain();
	void CreateBackBuffer();

	void SetRenderTarget(ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);

	void Clear(XMFLOAT4 color = XMFLOAT4(0.0f, 0.125f, 0.3f, 1.0f),
		ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);

	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }
};