#pragma once

class TerrainData
{
private:
	friend class QuadTree;
	typedef VertexTerrain VertexType;

	Texture* heightMap;

	vector<VertexType> prevData;
	vector<VertexType> vertices;
	vector<UINT> indices;

	UINT width, height;

public:
	TerrainData(wstring heightFile);
	~TerrainData();

	void CreateData();
	void CreateNormal();
	//void CreateTangent();

	void AlignVertexData();
};