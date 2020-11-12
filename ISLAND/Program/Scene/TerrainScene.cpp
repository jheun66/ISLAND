#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(256, 256);

	water = new LowPolyWater(256, 256);
	//water->position.y = 5.0f;

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
	water->SetDepthMap();
	// terrain 렌더하기
	terrain->SetShader(L"WaterDepthMap");
	float waterHeight = water->waterOption->data.waterHeight;
	float reflectionOffset = water->reflectionOffset;
	float refractionOffset = water->refractionOffset;
	terrain->SetClippingPlane(Float4(0, -1, 0, waterHeight + refractionOffset));
	terrain->Render();

	water->SetRefraction();
	// terrain 렌더하기
	terrain->SetShader(L"Terrain");
	terrain->SetClippingPlane(Float4(0, -1, 0, waterHeight + refractionOffset));
	terrain->Render();

	// SetReflection이 뒤에 있는 이유 카메라 위치를 바꿔줘서 Refraction위에 쓰려면 당연히 카메라 위치 세팅 다시해야함
	water->SetReflection();
	cube->Render();
	// terrain 렌더하기
	terrain->SetClippingPlane(Float4(0, 1, 0, -waterHeight + reflectionOffset));
	terrain->Render();
}

void TerrainScene::Render()
{
	terrain->SetClippingPlane(Float4(0, 0, 0, 0));
	terrain->Render();
	water->Render();
	cube->Render();
}

void TerrainScene::PostRender()
{
	terrain->PostRender();
	water->PostRender();
}
