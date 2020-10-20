#include "Framework.h"

Graphics* Graphics::instance = nullptr;

Graphics::Graphics(HWND hWnd)
	: hWnd(hWnd)
{
    SetGPUInfo();
	CreateDevcieAndSwapChain();
	CreateBackBuffer();
}

Graphics::~Graphics()
{
    renderTargetView->Release();

    swapChain->Release();
    deviceContext->Release();
    device->Release();
}

void Graphics::CreateDevcieAndSwapChain()
{
	RECT rc;
	// 핸들에서 정보를 가져옴
	GetClientRect(hWnd, &rc);

	// 잡다한거 제외하고 순 화면크기
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

    // 스왑체인과 관련되 정보를 담고 있는 구조체
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1; // 백버퍼 개수
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // unorm 양수인 0 ~ 1 까지 값
    // RefreshRate : 디스플레이 모드 갱신율(주사율 : Numerator / Denominator) (fps랑은 다름)
    if (bVsync)
    {
        sd.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;
        sd.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;
    }
    else
    {
        sd.BufferDesc.RefreshRate.Numerator = 0;
        sd.BufferDesc.RefreshRate.Denominator = 1;
    }
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;

    // 다중 표본화(안씀)
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    // 창모드
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // TODO : 외장 그래픽 사용하도록 변경하기

    vector<D3D_FEATURE_LEVEL> featureLevel
    {// 기능 수준, 무슨 버전 쓸지
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT maxVideoMemory = 0;
    for (int i = 0; i < adapterInfos.size(); i++)
    {
        if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)
        {
            maxVideoMemory = adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
            selectedAdapterIndex = i;
        }
    }

    gpuMemorySize = adapterInfos[selectedAdapterIndex]->adapterDesc.DedicatedVideoMemory;
    gpuDesc = adapterInfos[selectedAdapterIndex]->adapterDesc.Description;

    //  directx 2d와 3d 리소스의 상호운영을 가능하게하는 옵션
    UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
    creationFlags |= D3DCOMPILE_PREFER_FLOW_CONTROL
        | D3DCOMPILE_DEBUG
        | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    V(D3D11CreateDeviceAndSwapChain(
        adapterInfos[selectedAdapterIndex]->adapter,
        D3D_DRIVER_TYPE_UNKNOWN,
        0,
        creationFlags,
        featureLevel.data(),
        featureLevel.size(),
        D3D11_SDK_VERSION,
        &sd,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    ));

    gpuName.assign(gpuDesc.begin(), gpuDesc.end());
}

void Graphics::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    V(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer));
    V(device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView));

    backBuffer->Release();

    // 깊이 버퍼
    ID3D11Texture2D* depthBuffer;

    D3D11_TEXTURE2D_DESC depthDesc = {};
    depthDesc.Width = WIN_WIDTH;
    depthDesc.Height = WIN_HEIGHT;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    V(device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer));

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = depthDesc.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    V(device->CreateDepthStencilView(depthBuffer, &descDSV, &depthStencilView));
    depthBuffer->Release();
    SetRenderTarget();
}

void Graphics::EnumerateAdapters()
{
    IDXGIFactory1* factory;
    if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
        return;

    UINT index = 0;
    while (true)
    {
        IDXGIAdapter1* adapter = nullptr;
        HRESULT hr = factory->EnumAdapters1(index, &adapter);
        if (hr == DXGI_ERROR_NOT_FOUND)
            break;
        V(hr);

        D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
        ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
        adapterInfo->adapterOrdinal = index;
        adapter->GetDesc1(&adapterInfo->adapterDesc);
        adapterInfo->adapter = adapter;

        EnumerateAdapterOutput(adapterInfo);
        adapterInfos.push_back(adapterInfo);

        index++;
    }

    factory->Release();
}

bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo* adapterInfo)
{
    IDXGIOutput* output = nullptr;
    HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);
    if (hr == DXGI_ERROR_NOT_FOUND)
        return false;

    /*
        해상도
        감마설정
    */
    Graphics::D3DEnumOutputInfo* outputInfo = new Graphics::D3DEnumOutputInfo();
    ZeroMemory(outputInfo, sizeof(Graphics::D3DEnumOutputInfo));

    V(output->GetDesc(&outputInfo->outputDesc));
    
    outputInfo->output = output;

    UINT numModes = 0;
    DXGI_MODE_DESC* displayModes = nullptr;
    DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

    V(output->GetDisplayModeList
    (format,	// 설정한 포맷만 열거
        DXGI_ENUM_MODES_INTERLACED,
        &numModes,	// 모드가 몇갠지 넘어옴
        nullptr
    ));

    displayModes = new DXGI_MODE_DESC[numModes];
    V(output->GetDisplayModeList
    (
        format,
        DXGI_ENUM_MODES_INTERLACED,
        &numModes,
        displayModes
    ));

    // 맞는 해상도 가져와줌
    for (UINT i = 0; i < numModes; i++)
    {
        bool bCheck = true;
        bCheck &= displayModes[i].Width == WIN_WIDTH;
        bCheck &= displayModes[i].Height == WIN_HEIGHT;

        if (bCheck)
        {
            // 수직 동기화
            // (모니터의 주사율이 60hz이면 프레임도 60으로 144hz면 144로)
            // 갱신 주기 (refreshrate)
            outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
            outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
        }
    }
    adapterInfo->outputInfo = outputInfo;
    delete[] displayModes;

    return true;
}

void Graphics::SetGPUInfo()
{
    EnumerateAdapters();
}

void Graphics::SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
    if (rtv == nullptr)
        rtv = renderTargetView;
    if (dsv == nullptr)
        dsv = depthStencilView;
    
    deviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void Graphics::Clear(XMFLOAT4 color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
    if (rtv == nullptr)
        rtv = renderTargetView;
    if (dsv == nullptr)
        dsv = depthStencilView;

    deviceContext->ClearRenderTargetView(rtv, (float*)&color);
    deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::Present()
{
    swapChain->Present(0, 0);
}

Graphics::D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
    adapter->Release();
    delete outputInfo;
}

Graphics::D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
    output->Release();
}