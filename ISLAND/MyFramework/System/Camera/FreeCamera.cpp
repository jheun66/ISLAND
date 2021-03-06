#include "Framework.h"

FreeCamera::FreeCamera()
	:moveSpeed(60.0f), rotSpeed(3.0f), isFixed(false)
{
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Update()
{
	if (!isFixed)
	{
		Move();
		Rotation();
	}
	else
		Camera::Rotation();
	View();
}

void FreeCamera::PostRender()
{
	__super::PostRender();
	ImGui::SliderFloat("CamMoveSpeed", &moveSpeed, 1, 500);
	ImGui::SliderFloat("CamRotSpeed", &rotSpeed, 2.0f, 5.0f);
}

void FreeCamera::Move()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
			position += forward * moveSpeed * DELTA;
		if (KEY_PRESS('S'))
			position -= forward * moveSpeed * DELTA;
		if (KEY_PRESS('A'))
			position -= right * moveSpeed * DELTA;
		if (KEY_PRESS('D'))
			position += right * moveSpeed * DELTA;
		if (KEY_PRESS('Q'))
			position -= up * moveSpeed * DELTA;
		if (KEY_PRESS('E'))
			position += up * moveSpeed * DELTA;
	}

	position += forward * Control::Get()->GetWheel() * moveSpeed * DELTA;

}

void FreeCamera::Rotation()
{
	Vector3 value = MOUSEPOS - oldPos;

	if (KEY_PRESS(VK_RBUTTON))
	{
		rotation.x += value.y * rotSpeed * DELTA;
		rotation.y += value.x * rotSpeed * DELTA;

		Camera::Rotation();
	}

	oldPos = MOUSEPOS;
}
