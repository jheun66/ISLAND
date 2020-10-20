#pragma once
// GlobalBuffer

class MatrixBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		XMMATRIX matrix;
	}data;

public:
	MatrixBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
		data.matrix = XMMatrixIdentity();
	}

	void Set(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

};
