#pragma once

class QuadTree : public Transform
{
private:
	typedef VertexTerrain VertexType;

	const UINT divideCount = 16384;

	struct Node
	{
		float x, z, width;
		UINT triangleCount;

		Mesh* mesh;

		Node* children[4];
	};

	UINT triangleCount, drawCount;

	VertexType* vertices;

	Node* root;
	Frustum* frustum;

	UINT width, height;

	Material* material;

public:
	QuadTree(TerrainData* terrain);
	~QuadTree();

	void Update();
	void Render();
	void PostRender();

private:
	void RenderNode(Node* node);
	void DeleteNode(Node* node);

	void CalcMeshDimensions(UINT vertexCount,
		float& centerX, float& centerZ, float& width);
	void CreateTreeNode(Node* node, float positionX, float positionZ, float width);

	UINT ContainTriangleCount(float positionX, float positionZ, float width);
	bool IsTriangleContained(UINT index, float positionX, float positionZ, float width);
};