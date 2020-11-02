#include "Framework.h"
#include "QuadTreeTerrainScene.h"

QuadTreeTerrainScene::QuadTreeTerrainScene()
{
	terrainData = new TerrainData(L"Textures/IslandHeightMap.png");
	quadTree = new QuadTree(terrainData);

	water = new Water(128);
	water->position.y = 5.0f;

	scattering = new Scattering();
}

QuadTreeTerrainScene::~QuadTreeTerrainScene()
{
	delete terrainData;
	delete quadTree;

	delete water;
	delete scattering;
}

void QuadTreeTerrainScene::Update()
{
	water->Update();

	quadTree->Update();
	scattering->Update();
}

void QuadTreeTerrainScene::PreRender()
{
	scattering->PreRender();
	water->SetRefraction();
	water->SetReflection();
}

void QuadTreeTerrainScene::Render()
{
	scattering->Render();
	quadTree->Render();
	water->Render();
}

void QuadTreeTerrainScene::PostRender()
{
	quadTree->PostRender();
	water->PostRender();
	scattering->PostRender();
}
