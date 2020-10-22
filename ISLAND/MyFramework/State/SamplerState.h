#pragma once

class SamplerState
{
private:
	D3D11_SAMPLER_DESC desc;
	ID3D11SamplerState* state;

public:
	SamplerState();
	~SamplerState();

	void SetState(UINT slot = 0);

	void Filter(D3D11_FILTER value);
	void Address(D3D11_TEXTURE_ADDRESS_MODE value);

	// 좌표별로 다르게도 가능
	void AddressU(D3D11_TEXTURE_ADDRESS_MODE value);
	void AddressV(D3D11_TEXTURE_ADDRESS_MODE value);
	void AddressW(D3D11_TEXTURE_ADDRESS_MODE value);

	void Changed();
};