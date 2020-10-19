#pragma once

#include "resource.h"

class Window
{
private:
	// 싱글톤으로 관리
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
	// 크기는 기본값으로 초기화 타이틀만 입력받는 형식으로 
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