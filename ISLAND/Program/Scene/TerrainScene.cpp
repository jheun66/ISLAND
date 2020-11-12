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
	// terrain �����ϱ�
	terrain->SetShader(L"WaterDepthMap");
	float waterHeight = water->waterOption->data.waterHeight;
	float reflectionOffset = water->reflectionOffset;
	float refractionOffset = water->refractionOffset;
	terrain->SetClippingPlane(Float4(0, -1, 0, waterHeight + refractionOffset));
	terrain->Render();

	water->SetRefraction();
	// terrain �����ϱ�
	terrain->SetShader(L"Terrain");
	terrain->SetClippingPlane(Float4(0, -1, 0, waterHeight + refractionOffset));
	terrain->Render();

	// SetReflection�� �ڿ� �ִ� ���� ī�޶� ��ġ�� �ٲ��༭ Refraction���� ������ �翬�� ī�޶� ��ġ ���� �ٽ��ؾ���
	water->SetReflection();
	cube->Render();
	// terrain �����ϱ�
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
