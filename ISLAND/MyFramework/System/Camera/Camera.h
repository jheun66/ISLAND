#pragma once

class Transform;

struct Ray
{
	Vector3 position;
	Vector3 direction;
};

class Camera
{
protected:
	Vector3 position;
	Vector3 rotation;

	Vector3 forward;
	Vector3 right;
	Vector3 up;

	XMMATRIX matRotation;
	XMMATRIX matView;

	class ViewBuffer* viewBuffer;

	Vector3 oldPos;
public:
	Camera();
	virtual ~Camera();

	virtual void Update() = 0;
	virtual void Move() = 0;
	virtual void Rotation();
	virtual void View();

	// 업캐스트 위해서
	virtual void PostRender();
	virtual void SetTarget(Transform* value) {}

	void VSSet(UINT slot = 1);
	void GSSet(UINT slot = 1);

	Ray ScreenPointToRay(Vector3 pos);

	XMMATRIX GetView() { return matView; }
	Vector3 GetPos() { return position; }
	Vector3 GetRot() { return rotation; }

	void SetPosition(float x, float y, float z) { position = { x,y,z }; }
	void SetPosition(Vector3 value) { position = value; }
	void SetRotation(Vector3 value) { rotation = value; }
	void SetView(XMMATRIX view) { matView = view; }
};