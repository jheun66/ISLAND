#pragma once

class Terrain : public Transform
{
private:
	typedef VertexTerrain VertexType;

	Mesh* mesh = nullptr;
	Material* material = nullptr;

	Texture* heightMap = nullptr;
	Texture* gradientMap = nullptr;

	bool viewWire = false;

	// 2차원
	UINT width;
	UINT height;
	
	vector<VertexType> vertices;
	vector<UINT> indices;
	vector<VertexType> alignedVertices;

	RasterizerState* rs[2];

	// 노이즈 저장
	vector<vector<float>> noise; 

	float colorSpread;
	float halfSpread;
	vector<Float4> terrain_cols;
	float part;

	float maxH;
public:
	Terrain(UINT width, UINT hegiht);
	~Terrain();

	void Render();
	void Update();
	void PostRender();

	void SaveHeightMap(wstring path);
	void LoadHeightMap(wstring path);
	void AdjustGradient(wstring path);


private:
	void CreateTerrain();
	void AlignVertices();
	void CreateColor();
	void CreateNormal();
	void CreateCompute();

	Float4 calculateColor(float height, float amplitude);

	void GenerateNoise();
	float SmoothNoise(float x, float y);
	float Turbulence(float x, float y, float size);


};