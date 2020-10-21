#pragma once
// GlobalBuffer
// shader���� ��ġ�ؼ� �����°� ���꿡 ����

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

// ī�޶� ��ġ�� �˱� ���ϰ� ���� ���� ������!!
// ������� _41_42_43�� ī�޶� ��ǥ
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