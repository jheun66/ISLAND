#pragma once

class Terrain : public Transform
{
private:
	typedef VertexTerrain VertexType;

	class PlaneBuffer : public ConstantBuffer
	{
	private:
		struct Data
		{
			Float4 plane;
		}data;

	public:
		PlaneBuffer() : ConstantBuffer(&data, sizeof(Data))
		{
			data.plane = { 0, 0, 0, 0 };
		}

		void Set(Float4 value)
		{
			data.plane = value;
		}
	};

	Mesh* mesh = nullptr;
	Material* material = nullptr;

	Texture* heightMap = nullptr;
	Texture* gradientMap = nullptr;

	RasterizerState* rs[2];
	bool viewWire = false;

	// 2차원
	UINT width;
	UINT height;
	
	vector<VertexType> vertices;
	vector<UINT> indices;
	vector<VertexType> alignedVertices;

	// 노이즈 저장
	vector<vector<float>> noise; 

	float colorSpread;
	float halfSpread;
	vector<Float4> terrain_cols;
	float part;

	float maxH;

	PlaneBuffer* clippingPlane;
public:
	Terrain(UINT width, UINT hegiht);
	~Terrain();

	void Render();
	void Update();
	void PostRender();

	void SaveHeightMap(wstring path);
	void LoadHeightMap(wstring path);
	void AdjustGradient(wstring path);

	void SetShader(wstring shader);
	void SetClippingPlane(Float4 plane) { clippingPlane->Set(plane); }

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