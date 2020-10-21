#pragma once
// GlobalBuffer
// shader에는 전치해서 보내는게 연산에 편함

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

// 카메라 위치를 알기 편하게 같이 보내 버리자!!
// 역행렬의 _41_42_43이 카메라 좌표
class ViewBuffer : public ConstantBuffer
{
private:
	struct Data
	{
		XMMATRIX view;
		XMMATRIX invView;
	}data;

public:
	ViewBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
		data.view = XMMatrixIdentity();
		data.invView = XMMatrixIdentity();
	}

	void Set(XMMATRIX value)
	{
		data.view = XMMatrixTranspose(value);
		XMMATRIX tmp = XMMatrixInverse(nullptr, value);
		data.invView = XMMatrixTranspose(tmp);
	}

};