#include "Framework.h"

Transform::Transform(string tag)
	: tag(tag), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1),
	pivot(0, 0, 0), parent(nullptr)
{
	world = XMMatrixIdentity();
	worldBuffer = new MatrixBuffer();
}

Transform::~Transform()
{
	delete worldBuffer;
}

void Transform::UpdateWorld()
{
	// TODO : 부모 Scale 제외하고 내꺼만 적욛되도록 바꾸기!!

	world = XMMatrixTransformation(pivot.data, XMQuaternionIdentity(),
		scale.data, pivot.data, XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
		, position.data);

	if (parent != nullptr)
		world *= *parent;

	XMMatrixDecompose(&globalScale.data, &globalRotation.data,
		&globalPosition.data, world);

	worldBuffer->Set(world);
}

void Transform::SetWorldBuffer(UINT slot)
{
	worldBuffer->SetVSBuffer(slot);
}

Vector3 Transform::Forward()
{
	return XMVector3Normalize(XMVector3TransformNormal(kForward, world));
}

Vector3 Transform::Up()
{
	return XMVector3Normalize(XMVector3TransformNormal(kUp, world));
}

Vector3 Transform::Right()
{
	// 마지막 w 0
	return XMVector3Normalize(XMVector3TransformNormal(kRight, world));
}

Vector3 Transform::WorldPos()
{
	return globalPosition;
}

Vector4 Transform::WorldRot()
{
	return globalRotation.data;
}

Vector3 Transform::WorldScale()
{
	return globalScale;
}

void Transform::PostRender()
{
	//if (!isActive)
	//	return;

	//Vector3 screenPos;

	//Vector3 offset = { 0,10,0 };
	//Vector3 temp = globalPosition + offset;

	//screenPos = WorldToScreen(temp);

	//POINT size = { 100,100 };

	//RECT rect = { screenPos.x - size.x / 2, screenPos.y - size.y / 2, rect.left + size.x, rect.top + size.y };

	//DirectWrite::Get()->RenderText(ToWString(tag), rect);
}
