#pragma once

class Terrain : public Transform
{
private:
	typedef VertexTerrain VertexType;

	Mesh* mesh = nullptr;
	Material* material = nullptr;

	Texture* heightMap = nullptr;
	Texture* gradientMap = nullptr;
	Texture* alphaMap = nullptr;

	// 2차원
	UINT width;
	UINT height;
	
	vector<VertexType> vertices;
	vector<UINT> indices;

	RasterizerState* rs[2];

	// 노이즈 저장
	vector<vector<float>> noise; 


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
	void CreateNormal();
	void CreateTangent();
	void CreateCompute();

	void GenerateNoise();
	float SmoothNoise(float x, float y);
	float Turbulence(float x, float y, float size);


};