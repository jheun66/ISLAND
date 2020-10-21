#include "Framework.h"

#include "Scene/CubeScene.h"

Program::Program()
{
	scene = new CubeScene();
}

Program::~Program()
{
	delete scene;
}

void Program::Update()
{
	scene->Update();

	Environment::Get()->MainCamera()->Update();
	Control::Get()->SetWheel(0.0f);
}

void Program::PreRender()
{
	Environment::Get()->MainCamera()->VSSet(1);
	Environment::Get()->GetProjectionBuffer()->SetVSBuffer(2);

	Environment::Get()->SetViewport();

	scene->PreRender();
}

void Program::Render()
{
	// ����)
	// PreRender���� �ٱ� ���� �� ������.. �ٽ� ����
	Graphics::Get()->SetRenderTarget();

	Environment::Get()->MainCamera()->VSSet(1);
	Environment::Get()->GetProjectionBuffer()->SetVSBuffer(2);

	Environment::Get()->SetViewport();
	scene->Render();
}

void Program::PostRender()
{
	Environment::Get()->PostRender();
	scene->PostRender();

	PrintInfo();
}

void Program::PrintInfo()
{
	Graphics::Get()->GUI();
	
	ImGui::BeginMainMenuBar();
	{
		if (ImGui::BeginMenu("Option"))
		{
			// ���ʿ� üũ�ڽ�
			ImGui::Checkbox("FPS", &bFps);
			ImGui::Checkbox("MousePos", &bMouse);

			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

	if (bFps)
		PrintFPS();
	if (bMouse)
		PrintMousePos();
}

void Program::PrintFPS()
{
	static bool bOpen = true;
	//ImGui::SetNextWindowPos({ WIN_WIDTH - 100 ,15 });
	ImGui::Begin("FPS"
		, &bOpen
		, ImGuiWindowFlags_NoBackground
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
	);
	{
		string frame = "FPS : " + to_string((int)ImGui::GetIO().Framerate);
		ImGui::TextColored(ImVec4(1, 1, 1, 1), frame.c_str());
	}
	ImGui::End();
}

void Program::PrintMousePos()
{
	static bool bOpen = true;
	ImGui::SetNextWindowPos({ WIN_WIDTH - 100 , 30 });
	ImGui::SetNextWindowSize(ImVec2(200, 60));
	ImGui::Begin("MousePos"
		, &bOpen
		, ImGuiWindowFlags_NoBackground
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
	);
	{
		string x = "X : " + to_string(MOUSEPOS.x);
		string y = "Y : " + to_string(MOUSEPOS.y);
		ImGui::TextColored(ImVec4(1, 1, 1, 1), x.c_str());
		ImGui::TextColored(ImVec4(1, 1, 1, 1), y.c_str());
	}
	ImGui::End();
}
