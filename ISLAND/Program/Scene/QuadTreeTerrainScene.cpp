#include "Framework.h"
#include "QuadTreeTerrainScene.h"

QuadTreeTerrainScene::QuadTreeTerrainScene()
{
	terrainData = new TerrainData(L"Textures/IslandHeightMap.png");
	quadTree = new QuadTree(terrainData);
}

QuadTreeTerrainScene::~QuadTreeTerrainScene()
{
	delete terrainData;
	delete quadTree;
}

void QuadTreeTerrainScene::Update()
{
	quadTree->Update();
}

void QuadTreeTerrainScene::PreRender()
{
}

void QuadTreeTerrainScene::Render()
{
	quadTree->Render();
}

void QuadTreeTerrainScene::PostRender()
{
	quadTree->PostRender();
}
