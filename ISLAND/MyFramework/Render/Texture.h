#pragma once

// TODO : 2D때한 Texture2D 참고할 가치가 있음

class Texture
{
private:
	ScratchImage image;

	ID3D11ShaderResourceView* srv;

	// 한번만든 텍스쳐들 모아놓았다가 한꺼번에 지워주기
	static map<wstring, Texture*> totalTexture;

	Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);
	~Texture();

public:
	static Texture* Add(wstring file);
	static void Delete();

	void PSSet(UINT slot);

	vector<Float4> ReadPixels();

	UINT GetWidth() { return image.GetMetadata().width; }
	UINT GetHeight() { return image.GetMetadata().height; }

	ID3D11ShaderResourceView* GetSRV() { return srv; }
};