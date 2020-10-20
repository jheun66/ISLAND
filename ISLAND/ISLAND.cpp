#include "Framework.h"
#include "MyFramework/System/WindowsMessageMap.h"

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
    
    // 윈도우에서 만들어준 핸들임
    Graphics::Create(hWnd);

    // ImGui Setting
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE, DC);

    // Keyboard, Mouse

    // Timer

    Environment::Create();

    Program* program = new Program();

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
            // 내 프로그램 처리
            program->Update();

            program->PreRender();

            Graphics::Get()->Clear();

            // ImGui Frame
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            program->Render();
            program->PostRender();

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            Graphics::Get()->Present();
        }
    }

    // ImGui Delete
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // 종료 처리
    delete program;

    Environment::Delete();
    Graphics::Delete();

    return (int) msg.wParam;
}