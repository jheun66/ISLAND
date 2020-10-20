#pragma once

/*
DXGI �⺻���� ��Ȱ
�׷���ī�� ������ ����
���÷��� ����� ����
�����ġ�� ����
����ü�� ����(���� ���۸�)
*/


class Graphics
{
public:
	class D3DEnumOutputInfo;
	class D3DEnumAdapterInfo
	{
	public:
		~D3DEnumAdapterInfo();

		UINT adapterOrdinal = 0;		// Ordinal : ���� (ù��° �ι�°)		Cardinal : ��� (���̻��)
		IDXGIAdapter1* adapter = nullptr;
		DXGI_ADAPTER_DESC1 adapterDesc;

		Graphics::D3DEnumOutputInfo* outputInfo = nullptr;
	private:
		// ���Կ����� �����Ǹ� ���� �ƹ��͵� ���ϰ� �� (���� ����, ���� ���� �ƹ� ���� ������)
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

	// direct�� �ϵ忡 ���� ������ ó���ϴµ� device�� cpu, context�� gpu�� ������ ó���Ѵ�.
	ID3D11Device* device;                       // CPU, ���ҽ� �Ҵ�
	ID3D11DeviceContext* deviceContext;         // GPU, ������
									// View�� ������ GPU ����
	IDXGISwapChain* swapChain;                  // ���� ���� ����
	ID3D11RenderTargetView* renderTargetView;   // �� ����
	ID3D11DepthStencilView* depthStencilView;

	UINT gpuMemorySize = 0;
	wstring gpuDesc = L"";

	string gpuName = "";

	vector<Graphics::D3DEnumAdapterInfo*> adapterInfos;
	int selectedAdapterIndex = 0;

	// ���� ����ȭ ����
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

	// �����ֱ�
	void Clear(XMFLOAT4 color = XMFLOAT4(0.0f, 0.125f, 0.3f, 1.0f),
		ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);

	// ȭ�鿡 ���
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

private:
	void CreateDevcieAndSwapChain();
	void CreateBackBuffer();

	// ����̽� ����(�׷���ī��)
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo);
	void SetGPUInfo();

};