#pragma once

/*
DXGI 기본적인 역활
그래픽카드 정보의 열거
디스플레이 모드의 열거
출력장치의 나열
스왑체인 생성(더블 버퍼링)
*/


class Graphics
{
public:
	class D3DEnumOutputInfo;
	class D3DEnumAdapterInfo
	{
	public:
		~D3DEnumAdapterInfo();

		UINT adapterOrdinal = 0;		// Ordinal : 서수 (첫번째 두번째)		Cardinal : 기수 (일이삼사)
		IDXGIAdapter1* adapter = nullptr;
		DXGI_ADAPTER_DESC1 adapterDesc;

		Graphics::D3DEnumOutputInfo* outputInfo = nullptr;
	private:
		// 대입연산자 재정의를 통해 아무것도 안하게 함 (깊은 복사, 얕은 복사 아무 걱정 없도록)
		const D3DEnumAdapterInfo& operator =
			(const D3DEnumAdapterInfo& rhs);

	};

	class D3DEnumOutputInfo
	{
	public:
		~D3DEnumOutputInfo();

		IDXGIOutput* output = nullptr;
		DXGI_OUTPUT_DESC outputDesc;

		UINT numerator = 0;
		UINT denominator = 1;

	private:
		const D3DEnumOutputInfo& operator =
			(const D3DEnumOutputInfo& rhs);
	};

private:
	HWND hWnd;

	// direct는 하드에 직접 접근해 처리하는데 device는 cpu, context는 gpu를 대행해 처리한다.
	ID3D11Device* device;                       // CPU, 리소스 할당
	ID3D11DeviceContext* deviceContext;         // GPU, 렌더링
									// View가 붙으면 GPU 관련
	IDXGISwapChain* swapChain;                  // 더블 버퍼 관리
	ID3D11RenderTargetView* renderTargetView;   // 백 버퍼
	ID3D11DepthStencilView* depthStencilView;

	UINT gpuMemorySize = 0;
	wstring gpuDesc = L"";

	string gpuName = "";

	vector<Graphics::D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	// 수직 동기화 여부
	bool bVsync = false;


	static Graphics* instance;

	Graphics(HWND hWnd);
	~Graphics();


public:
	static Graphics* Get() { return instance; }
	static void Create(HWND hWnd) { instance = new Graphics(hWnd); }
	static void Delete() { delete instance; }

	void SetRenderTarget(ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);

	// 지워주기
	void Clear(XMFLOAT4 color = XMFLOAT4(0.0f, 0.125f, 0.3f, 1.0f),
		ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);

	// 화면에 출력
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

private:
	void CreateDevcieAndSwapChain();
	void CreateBackBuffer();

	// 디바이스 관련(그래픽카드)
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);
	void SetGPUInfo();

};