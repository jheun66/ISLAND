#include "Framework.h"
#include "QuadTreeTerrainScene.h"

QuadTreeTerrainScene::QuadTreeTerrainScene()
{
	terrainData = new TerrainData(L"Textures/IslandHeightMap.png");
	quadTree = new QuadTree(terrainData);

	scattering = new Scattering();
}

QuadTreeTerrainScene::~QuadTreeTerrainScene()
{
	delete terrainData;
	delete quadTree;

	delete scattering;
}

void QuadTreeTerrainScene::Update()
{

	quadTree->Update();
	scattering->Update();
}

void QuadTreeTerrainScene::PreRender()
{
	scattering->PreRender();
}

void QuadTreeTerrainScene::Render()
{
	scattering->Render();
	quadTree->Render();
}

void QuadTreeTerrainScene::PostRender()
{
	quadTree->PostRender();
	scattering->PostRender();
}
