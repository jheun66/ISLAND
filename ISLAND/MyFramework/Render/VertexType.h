#pragma once

// VertexType ����

struct VertexUV
{
	Float3 position;
	Float2 uv;

	VertexUV() :position(0, 0, 0), uv(0, 0)
	{

	}
};

// �𵨿��� ����Ҳ�
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


// �ͷ��ο��� ����Ҳ�
struct VertexTerrain
{
	Float3 position;
	Float2 uv;
	Float3 normal;
	Float3 tangent;
	float alpha[4];

	VertexTerrain() : position(0, 0, 0), uv(0, 0), normal(0, 0, 0), tangent(0,0,0), alpha{}
	{

	}
};