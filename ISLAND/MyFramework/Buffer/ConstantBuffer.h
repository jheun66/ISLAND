#pragma once

class ConstantBuffer
{
private:
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;

protected:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	void MapData();

public:
	// shader 마다 만들어 줘야함
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);
	void SetGSBuffer(UINT slot);
};