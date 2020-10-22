#include "Framework.h"
#include "QuadScene.h"

QuadScene::QuadScene()
{
	quad = new Quad();
}

QuadScene::~QuadScene()
{
	delete quad;
}

void QuadScene::Update()
{
	quad->Update();
}

void QuadScene::PreRender()
{

}

void QuadScene::Render()
{
	quad->Render();
}

void QuadScene::PostRender()
{
	quad->PostRender();
}
