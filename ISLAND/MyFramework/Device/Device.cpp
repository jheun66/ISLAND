#include "Framework.h"

Device* Device::instance = nullptr;

Device::Device(HWND hWnd)
	: hWnd(hWnd)
{
	CreateDevcieAndSwapChain();
	CreateBackBuffer();
}

Device::~Device()
{
    renderTargetView->Release();

    swapChain->Release();
    deviceContext->Release();
    device->Release();
}

void Device::CreateDevcieAndSwapChain()
{
	RECT rc;
	// �ڵ鿡�� ������ ������
	GetClientRect(hWnd, &rc);

	// ����Ѱ� �����ϰ� �� ȭ��ũ��
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

    // ����ü�ΰ� ���õ� ������ ��� �ִ� ����ü
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1; // ����� ����
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // unorm ����� 0 ~ 1 ���� ��
    // RefreshRate : ���÷��� ��� ������(�ֻ��� : Numerator / Denominator) (fps���� �ٸ�)
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;

    // ���� ǥ��ȭ(�Ⱦ�)
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    // â���
    sd.Windowed = true;

    // TODO : ���� �׷��� ����ϵ��� �����ϱ�

    V(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &swapChain,
        &device,
        nullptr,
        &deviceContext
    ));
}

void Device::CreateBackBuffer()
{
    ID3D11Texture2D* backBuffer;

    V(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer));
    V(device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView));

    backBuffer->Release();
}

void Device::SetRenderTarget(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
    if (rtv == nullptr)
        rtv = renderTargetView;

    deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
}

void Device::Clear(XMFLOAT4 color, ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv)
{
    if (rtv == nullptr)
        rtv = renderTargetView;

    deviceContext->ClearRenderTargetView(rtv, (float*)&color);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}
