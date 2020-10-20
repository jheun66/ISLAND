#pragma once

// 주석 모음

// ID3D11 : com Interface , 이중포인터 사용

// device의 자원은 buffer와 texture
// buffer에 담아 RAM에서 VRAM으로 전달
// Texture 1D,2D,3D, pixel,texel
// 텍스처에 있는 자원들
// 1. RenderTargetView		그려줄애, 도화지 같은거 (쓰기 전용) : 그릴 수있는애
// 2. ShaderResourceView	효과??, 그래픽 카드를 이용해서 줄수잇는 효과, 자원?? (읽기 전용): 있는걸 가져와 쓰겠다
// 3. DepthStencilView		깊이같은걸 주는 자원 (3D할때 사용)
// 4. UnorderedAccessView	순서상관없이 접근하는 자원 (읽기,쓰기 둘다 됨) 

// Device Context : DC
// 뭔가를 그리는 거와 관려있음.
// 그 안에 밑에께 들어잇음 
// Rendering Pipeline : 그리는 단계??
//						IA (Input Assembler(입력 조립기))
//					 	그리기 위해 필요한 정보들을 넣어주는 단계 
//						VS (Vertex Shader)	정점(Vertex)	Shader: 그래픽카드를 제어할 수 있는 함수들의 모음
//						정점들을 조작						
//						RS (Rasterizer Stage)
//						3D 공간을 2D(화면)에 표현하기 위해 픽셀화??
//						PS (Pixel Shader)
//						픽셀들을 조작 ( 빛에 따라 색이 바뀌는 등 )
//						OM (Output Merger)
//						최종적으로 RenderTagetView에 그려주는 단계

// 우리가 코딩할 수있는건 Shader 붙은 애들	
// 나머지는 설정을 입력해주는거 밖에 못함

// DXGI 소프트웨어와 하드웨어(그래픽 카드) 사이에서 도와줌 , swapchain : 더블버퍼링을 위해 있는 애, adapter : 그래픽 카드, output : 모니터
// SwapChain : 도화지를 하나더 만들고 그 둘을 번갈아 그릴때마다 앞뒤로 보이는게 안보이게 하는데
//			   (지우는 과정이 안보임, 깜빡이는게 사라짐) 이때 계속돌아가게 함

// Viewport : 그린 공간안에서 화면에 보여질 영역 

// d3dxcolor : RGBA float 4개(16바이트) 구조체 (0 부터 1까지의 값들을 사용) 정규화때문