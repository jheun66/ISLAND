#pragma once

class LowPolyWater : public Transform
{
private:
	typedef VertexLowPolyWater VertexType;

	class WaterBuffer : public ConstantBuffer
	{
	public:
		struct Data
		{
			Float4 color = Float4(0.2f, 0.3f, 1.0f, 1.0f);

			float waveTranslation = 0.0f;
			float waveScale = 0.05f;
			float shininess = 0.0f;
			float alpha = 0.5f;

			float waveSpeed = 0.05f;
			float padding[3] = {};
		}data;

		WaterBuffer() : ConstantBuffer(&data, sizeof(Data))
		{
		}
	};

	WaterBuffer* buffer;

	Material* material;
	Mesh* mesh;

	vector<VertexType> vertices;
	vector<UINT> indices;
	vector<VertexType> alignedVertices;

	Reflection* reflection;
	Refraction* refraction;

	TimeBuffer* timeBuffer;

	RasterizerState* rasterizerState[2];
	BlendState* blendState[2];

	float width;
	float height;

public:
	LowPolyWater(float width, float hieght);
	~LowPolyWater();

	void Update();

	void SetReflection();
	void SetRefraction();
	void Render();
	void PostRender();

private:
	void CreateMesh();
	VertexLowPolyWater CalcIndicators(VertexType* four, UINT curVertex, UINT vertex1, UINT vertex2);
};