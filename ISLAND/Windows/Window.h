#pragma once

#include "resource.h"

class Window
{
private:
	// �̱������� ����
	class WindowClass
	{
	public:
		static const WCHAR* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr WCHAR wndClassName[100] = L"Window Class Name";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	// ũ��� �⺻������ �ʱ�ȭ Ÿ��Ʋ�� �Է¹޴� �������� 
	Window(const WCHAR* title, int width = WIN_WIDTH, int height = WIN_HEIGHT) noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;
};