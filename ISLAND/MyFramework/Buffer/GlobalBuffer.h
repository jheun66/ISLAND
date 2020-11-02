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

class LightBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Light lights[MAX_LIGHT];

		UINT lightCount;
		float padding[3];

		Float4 ambient;
		Float4 ambientCeil;
	}data;

	LightBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
		data.lightCount = 0;

		data.ambient = { 0.1f,0.1f,0.1f,1.0f };
		data.ambientCeil = { 0.1f,0.1f,0.1f,1.0f };
	}

	void Add(Light light)
	{
		data.lights[data.lightCount++] = light;
	}
	void Add()
	{
		data.lightCount++;
	}

};

// shader�� �ð��� ������ ����
class TimeBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		float time;

		Float3 padding;

		Data() : time(0)
		{}
	}data;

	TimeBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
	}
};

// �ɼ��̳� ���õ��� ������ �뵵
class SettingBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int option[4];

		Data() :option{}
		{}
	}data;

	SettingBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
	}
};


class BoneBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		Matrix bones[MAX_MODEL_BONE];
	}data;

	BoneBuffer() : ConstantBuffer(&data, sizeof(Data))
	{
		for (UINT i = 0; i < MAX_MODEL_BONE; i++)
			data.bones[i] = XMMatrixIdentity();
	}

	void Add(Matrix matrix, UINT index)
	{
		//data.bones[index] = matrix;
		data.bones[index] = XMMatrixTranspose(matrix);
	}
};
