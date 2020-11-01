#include "Framework.h"
#include "QuadTreeTerrainScene.h"

QuadTreeTerrainScene::QuadTreeTerrainScene()
{
	terrainData = new TerrainData(L"Textures/IslandHeightMap.png");
	quadTree = new QuadTree(terrainData);

	water = new Water(128);
	water->position.y = 5.0f;
}

QuadTreeTerrainScene::~QuadTreeTerrainScene()
{
	delete terrainData;
	delete quadTree;

	delete water;
}

void QuadTreeTerrainScene::Update()
{
	water->Update();

	quadTree->Update();
}

void QuadTreeTerrainScene::PreRender()
{
	water->SetRefraction();
	water->SetReflection();
}

void QuadTreeTerrainScene::Render()
{
	quadTree->Render();
	water->Render();
}

void QuadTreeTerrainScene::PostRender()
{
	quadTree->PostRender();
	water->PostRender();
}
