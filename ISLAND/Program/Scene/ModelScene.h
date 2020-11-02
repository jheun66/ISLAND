#pragma once

class ModelScene : public Scene
{
private:
	ModelReader* reader;
	ModelRender* render;
	ModelAnimator* animator;

public:
	ModelScene();
	~ModelScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};