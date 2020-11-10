#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(256, 256);

	water = new Water(128);
	water->position.y = 5.0f;

	cube = new Cube();
	cube->SetControl(false);
	cube->SetPos(XMFLOAT3(2, 10, 2));
}

TerrainScene::~TerrainScene()
{
	delete terrain;
	delete water;

	delete cube;
}

void TerrainScene::Update()
{
	water->Update();
	terrain->Update();

	cube->Update();
}

void TerrainScene::PreRender()
{
	water->SetRefraction();

	water->SetReflection();
	cube->Render();

}

void TerrainScene::Render()
{
	terrain->Render();
	water->Render();

	cube->Render();
}

void TerrainScene::PostRender()
{
	terrain->PostRender();
	water->PostRender();
}
