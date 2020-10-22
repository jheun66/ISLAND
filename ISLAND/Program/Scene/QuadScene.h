#pragma once

class QuadScene : public Scene
{
private:
	Quad* quad;

public:
	QuadScene();
	~QuadScene();

	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
};