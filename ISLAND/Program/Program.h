#pragma once

class Program
{
private:
	Scene* scene;

	bool bFps = true;
	bool bMouse = true;

public:
	Program();
	~Program();

	void Update();

	void PreRender();
	void Render();
	void PostRender();

	void PrintInfo();
	void PrintFPS();
	void PrintMousePos();
};