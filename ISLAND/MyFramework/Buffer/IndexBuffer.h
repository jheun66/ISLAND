#pragma once

class IndexBuffer
{
private:
	ID3D11Buffer* buffer;
	UINT count;
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void IASet();
	UINT GetIndexCount() { return count; }
};