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

// shader에 시간을 전달할 버퍼
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

// 옵션이나 세팅등을 보내는 용도
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
