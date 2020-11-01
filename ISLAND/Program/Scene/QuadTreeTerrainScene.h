#pragma once

class QuadTreeTerrainScene :public Scene
{
private:
	QuadTree* quadTree;
	TerrainData* terrainData;

	Water* water;

public:
	QuadTreeTerrainScene();
	~QuadTreeTerrainScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};