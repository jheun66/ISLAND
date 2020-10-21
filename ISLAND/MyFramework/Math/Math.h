#pragma once

#define LERP(s, e, t) (s + (e - s) * t)

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;

const XMVECTORF32 kRight = { 1, 0, 0 };
const XMVECTORF32 kUp = { 0, 1, 0 };
const XMVECTORF32 kForward = { 0, 0, 1 };

class Vector3;

namespace GameMath
{
	float Saturate(const float& value);

	int Random(int min, int max);
	float Random(float min, float max);

	float Distance(const Vector3& v1, const Vector3& v2);

	Vector3 ClosestPointOnLineSegment(const Vector3& A, const Vector3& B, const Vector3& point);
}