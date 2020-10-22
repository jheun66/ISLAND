#pragma once

#include "targetver.h"
// 컴파일러에게 외부 MFC 오버헤더를 포함하지 말도록 지시
#define WIN32_LEAN_AND_MEAN
// min max 충돌방지용
#define NOMINMAX

// 화면 크기
#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

// 윈도우 왼쪽 위 위치(요건 좀 자세히 알아보기)
#define WIN_START_X 100
#define WIN_START_Y 100

// 디버그 아니면 무시
#ifdef NDEBUG
#define V(hr) hr
#else
#define V(hr) assert(SUCCEEDED(hr))
#endif

#define DEVICE Graphics::Get()->GetDevice()
#define DC Graphics::Get()->GetDeviceContext()

#define KEY_DOWN(k) Control::Get()->Down(k)
#define KEY_PRESS(k) Control::Get()->Press(k)
#define KEY_UP(k) Control::Get()->Up(k)

#define MOUSEPOS Control::Get()->GetMouse()

#define DELTA Timer::Get()->Delta()

#define CAMERA Environment::Get()->MainCamera()

// Windows 헤더 파일
#include <Windows.h>

// 자주 쓰는 헤더 파일
#include <assert.h>
#include <vector>
#include <map>
#include <string>
#include <tchar.h>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <functional>

// direct 라이브러리 추가
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
// TODO : 나중에 추가하기

// 프로젝트 속성 - 링커 - 입력 - 추가 종속성에서 추가해 줘도 된다.
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
// interface id 있는 라이브러리 
#pragma comment(lib, "dxguid.lib")


// ImGui
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

// DirectXTex
#include "../DirectXTex/DirectXTex.h"

// 자주 사용하는 namespace
using namespace DirectX;
using namespace std;

// Framework

// System 관련
#include "MyFramework/Math/Math.h"
#include "MyFramework/Math/Vector3.h"
#include "MyFramework/Math/Transform.h"

#include "MyFramework/System/Window.h"
#include "MyFramework/System/Graphics.h"
#include "MyFramework/System/Timer.h"
#include "MyFramework/System/Control/Control.h"

#include "MyFramework/System/Camera/Camera.h"
#include "MyFramework/System/Camera/FreeCamera.h"
#include "MyFramework/System/Camera/FollowCamera.h"

#include "MyFramework/State/RasterizerState.h"
#include "MyFramework/State/SamplerState.h"

#include "MyFramework/System/Environment.h"


#include "MyFramework/Utility/Utility.h"
#include "MyFramework/Utility/Path.h"

#include "MyFramework/Shader/Shader.h"

#include "MyFramework/Shader/VertexShader.h"
#include "MyFramework/Shader/PixelShader.h"
#include "MyFramework/Shader/ComputeShader.h"
#include "MyFramework/Shader/GeometryShader.h"

#include "MyFramework/Buffer/VertexBuffer.h"
#include "MyFramework/Buffer/IndexBuffer.h"
#include "MyFramework/Buffer/ConstantBuffer.h"
#include "MyFramework/Buffer/GlobalBuffer.h"

#include "MyFramework/Render/VertexType.h"
#include "MyFramework/Render/Texture.h"
#include "MyFramework/Render/Mesh.h"
#include "MyFramework/Render/Material.h"


// Game Object
#include "GameObject/Basic/Cube.h"
#include "GameObject/Basic/Quad.h"


// Program Header
#include "Program/Scene/Scene.h"
#include "Program/Program.h"


// 일단 주석하기
//// C 런타임 헤더 파일입니다.
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>

extern HWND hWnd;

