#pragma once

class QuadTreeTerrainScene :public Scene
{
private:
	QuadTree* quadTree;
	TerrainData* terrainData;

public:
	QuadTreeTerrainScene();
	~QuadTreeTerrainScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};