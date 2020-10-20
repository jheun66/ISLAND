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
}
