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
	// shader ���� ����� �����
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);
	void SetGSBuffer(UINT slot);
};