#pragma once

// TODO : 2D���� Texture2D ������ ��ġ�� ����

class Texture
{
private:
	ScratchImage image;

	ID3D11ShaderResourceView* srv;

	// �ѹ����� �ؽ��ĵ� ��Ƴ��Ҵٰ� �Ѳ����� �����ֱ�
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