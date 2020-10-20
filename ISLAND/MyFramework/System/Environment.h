#pragma once

class MatrixBuffer;

class Environment
{
private:
	// 나중에 카메라로 분리 할꺼
	MatrixBuffer* viewBuffer;
	MatrixBuffer* projectionBuffer;

	static Environment* instance;
	Environment();
	~Environment();
public:
	static Environment* Get() { return instance; }
	static void Create() { instance = new Environment(); }
	static void Delete() { delete instance; }

	MatrixBuffer* GetView() { return viewBuffer; }
	MatrixBuffer* GetProjection() { return projectionBuffer; }

private:
	void CreateViewort();
	void CreatePerspective();

};