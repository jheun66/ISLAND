#pragma once

class FreeCamera : public Camera
{
private:
	float moveSpeed;
	float rotSpeed;

	bool isFixed;
public:
	FreeCamera();
	~FreeCamera();

	void Update() override;
	void PostRender() override;

	void SetFixed(bool isFixed) { this->isFixed = isFixed; }

private:
	void Move() override;
	void Rotation() override;
};