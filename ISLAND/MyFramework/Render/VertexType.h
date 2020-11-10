#pragma once

// VertexType 모음

struct VertexUV
{
	Float3 position;
	Float2 uv;

	VertexUV() :position(0, 0, 0), uv(0, 0)
	{

	}
};

// 모델에서 사용할꺼
struct VertexUVNormalTangentBlend
{
	Float3 position;
	Float2 uv;
	Float3 normal;
	Float3 tangent;
	Float4 blendIndices;
	Float4 blendWeights;

	VertexUVNormalTangentBlend() : position(0, 0, 0), uv(0, 0), normal(0, 0, 0), tangent(0, 0, 0),
		blendIndices(0, 0, 0, 0), blendWeights(0, 0, 0, 0)
	{

	}
};


// 터레인에서 사용할꺼
struct VertexTerrain
{
	Float3 position;
	Float4 color;
	Float2 uv;
	Float3 normal;

	VertexTerrain() : position(0, 0, 0), color(1, 1, 1, 1), uv(0, 0), normal(0, 0, 0)
	{
	}
};


struct VertexLowPolyWater
{
	Float3 position;
	Float4 indicators;

	VertexLowPolyWater() : position(0, 0, 0), indicators(0, 0, 0, 0)
	{
	}
};