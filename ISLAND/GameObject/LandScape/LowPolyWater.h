#pragma once

class LowPolyWater : public Transform
{
private:
	// 카메라의 nearfar 평면
	class NearFarBuffer : public ConstantBuffer
	{
	public:
		struct Data
		{
			float nearPlane;
			float farPlane;
			float dummy[2];
		}data;

		NearFarBuffer() :ConstantBuffer(&data, sizeof(Data))
		{
			data.nearPlane = 0.1f;
			data.farPlane = 1000.0f;
		}
	};

	class WaterOptionBuffer : public ConstantBuffer
	{
	public:
		struct Data
		{
			float waterHeight;
			float waveLength;
			float waveAmplitude;
			float dummy;
		}data;

		WaterOptionBuffer() :ConstantBuffer(&data, sizeof(Data))
		{
			data.waterHeight = 5.0f;
			data.waveLength = 4.0f;
			data.waveAmplitude = 0.2f;
		}
	};

	// 물깊이 수정하게하기 위해 
	friend class TerrainScene;

	typedef VertexLowPolyWater VertexType;

	Material* material;
	Mesh* mesh;

	vector<VertexType> vertices;
	vector<UINT> indices;
	vector<VertexType> alignedVertices;

	Reflection* reflection;
	Refraction* refraction;

	float reflectionOffset = -0.1f;
	float refractionOffset = -3.0f;

	DepthMap* depthMap;

	RasterizerState* rs[2];
	bool viewWire = false;

	NearFarBuffer* nearFarBuffer;
	WaterOptionBuffer* waterOption;
	TimeBuffer* timeBuffer;

	float width;
	float height;

public:
	LowPolyWater(float width, float hieght);
	~LowPolyWater();

	void Update();

	void SetDepthMap();
	void SetReflection();
	void SetRefraction();
	void Render();
	void PostRender();

private:
	void CreateMesh();
	VertexLowPolyWater CalcIndicators(VertexType* four, UINT curVertex, UINT vertex1, UINT vertex2);
};