#include "Framework.h"

#include "Scene/CubeScene.h"

Program::Program()
{
	scene = new CubeScene();
}

Program::~Program()
{
	delete scene;

	Shader::Delete();
}

void Program::Update()
{
	scene->Update();
}

void Program::PreRender()
{
	scene->PreRender();
}

void Program::Render()
{
	Environment::Get()->GetView()->SetVSBuffer(1);
	Environment::Get()->GetProjection()->SetVSBuffer(2);

	scene->Render();
}

void Program::PostRender()
{
	scene->PostRender();

	PrintInfo();
}

void Program::PrintInfo()
{

	ImGui::BeginMainMenuBar();
	{

		if (ImGui::BeginMenu("Option"))
		{
			// 왼쪽에 체크박스
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
	ImGui::SetNextWindowPos({ WIN_WIDTH - 100 ,15 });
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
	//static bool bOpen = true;
	//ImGui::SetNextWindowPos({ WIN_WIDTH - 100 , 30 });
	//ImGui::SetNextWindowSize(ImVec2(200, 60));
	//ImGui::Begin("MousePos"
	//	, &bOpen
	//	, ImGuiWindowFlags_NoBackground
	//	| ImGuiWindowFlags_NoTitleBar
	//	| ImGuiWindowFlags_NoResize
	//	| ImGuiWindowFlags_NoMove
	//);
	//{
	//	string x = "X : " + to_string((int)Mouse::Get()->GetPosition().x);
	//	string y = "Y : " + to_string((int)Mouse::Get()->GetPosition().y);
	//	ImGui::TextColored(ImVec4(1, 1, 1, 1), x.c_str());
	//	ImGui::TextColored(ImVec4(1, 1, 1, 1), y.c_str());
	//}
	//ImGui::End();
}
