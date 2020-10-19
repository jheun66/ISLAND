#pragma once

class VertexShader;
class PixelShader;
class ComputeShader;
class GeometryShader;

class Shader
{
private:
	static map<wstring, Shader*> totalShader;

public:
	static VertexShader* AddVS(wstring file, string vsName = "main");
	static PixelShader* AddPS(wstring file, string psName = "main");
	static ComputeShader* AddCS(wstring file, string csName = "main");
	static GeometryShader* AddGS(wstring file, string gsName = "main");

	static void Delete();

	virtual void Set() = 0;
};