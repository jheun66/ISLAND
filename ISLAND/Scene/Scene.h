#pragma once

// ��� ���� Scene�� ��ӹ޾� ������
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};