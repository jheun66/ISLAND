#pragma once

// 모든 씬은 Scene을 상속받아 생성함
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void Update() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};