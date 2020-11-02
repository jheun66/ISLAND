#include "Framework.h"
#include "ModelScene.h"

ModelScene::ModelScene()
{
	//reader = new ModelReader();
	//reader->ReadFile("ModelData/Models/SK_Crow.FBX");
	//reader->ExportMesh("Crow/SK_Crow");
	//reader->ExportMaterial("Crow/SK_Crow");

	//render = new ModelRender("Crow/SK_Crow");
	//Transform* transform = render->AddTransform();

	reader = new ModelReader();
	reader->ReadFile("ModelData/Animations/Crow/ANIM_Crow_EatSomething.FBX");
	reader->ExportClip(0, "Crow/Eat");

	animator = new ModelAnimator("Crow/SK_Crow");
	animator->ReadClip("Crow/Eat");
	Transform* transform = animator->AddTransform();
	transform->UpdateWorld();
	animator->PlayClip(0, 0);

}

ModelScene::~ModelScene()
{
	delete reader;
	delete animator;
}

void ModelScene::Update()
{
	animator->Update();
}

void ModelScene::PreRender()
{
}

void ModelScene::Render()
{
	animator->Render();
}

void ModelScene::PostRender()
{
	animator->PostRender();
}
