#include "Framework.h"
#include "Windows/WindowsMessageMap.h"




//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Window window(L"ISLAND");

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ISLAND));

    MSG msg = {};

    // TODO : 초기화 파트
    // Device 생성

    // Imgui 초기화

    // Keyboard, Mouse

    // Timer

    // Enviroment

    // Program

    // PeekMessage 처리로 변경
    while (msg.message != WM_QUIT)
    {
        // 메시지 들어올때만
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 프로시저로 메시지 넘김
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // TODO : 
            // 내 프로그램 처리
        }
    }

    // TODO :
    // 종료 처리

    return (int) msg.wParam;
}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    //static WindowsMessageMap mm;
//    // 디버깅으로 들어오는 메시지 확인 가능
//    //OutputDebugString(mm(message, lParam, wParam).c_str());
//
//    // 필요한 윈도우 메시지 찾고 싶으면 
//    // https://wiki.winehq.org/List_Of_Windows_Messages
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_GETMINMAXINFO:
//        //화면 크기 제어
//        ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WIN_WIDTH;
//        ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WIN_HEIGHT;
//        ((MINMAXINFO*)lParam)->ptMinTrackSize.x = WIN_WIDTH;
//        ((MINMAXINFO*)lParam)->ptMinTrackSize.y = WIN_HEIGHT;
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
