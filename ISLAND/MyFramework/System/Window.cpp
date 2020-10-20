#include "Framework.h"

// ���� ������ �����ص�
HWND hWnd;
// Inner Class

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	// �ϳ��� DC, �ٽ� �׸���
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_ICON2));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCEW(IDC_ISLAND);
	wc.lpszClassName = GetName();
	wc.hIconSm = LoadIcon(GetInstance(), MAKEINTRESOURCE(IDI_ICON2));;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const WCHAR* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


// Window Class
Window::Window(const WCHAR* title, int width, int height) noexcept
{
	// calculate window size based on desired client region size
	RECT rc;
	rc.left = WIN_START_X;
	rc.top = WIN_START_Y;
	rc.right = width + rc.left;
	rc.bottom = height + rc.top;

	AdjustWindowRect(&rc, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		WindowClass::GetName(), title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		WIN_START_X, WIN_START_Y, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	// �޴� ���ֱ�
	SetMenu(hWnd, nullptr);

	// SW_SHOWDEFAULT �ʱ� flag ������
	ShowWindow(hWnd, SW_SHOWDEFAULT);

	// �ﰢ ����
	UpdateWindow(hWnd);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

// �� ���ذ� �ȵ�
// https://youtu.be/D-PC-huX-l8  �ٽ� ����
LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

// ImGui WndProc(message ó��) ���漱�� 
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// ���� WndProc
LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    // �ʿ��� ������ �޽��� ã�� ������ 
    // https://wiki.winehq.org/List_Of_Windows_Messages

	// ImGui �޽��� ó��
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;


	switch (msg)
	{
	case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_GETMINMAXINFO:
        //ȭ�� ũ�� ����
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WIN_WIDTH;
        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WIN_HEIGHT;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = WIN_WIDTH;
        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = WIN_HEIGHT;
        break;

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}