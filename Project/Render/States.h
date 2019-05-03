#pragma once

class States
{
public:
	States();
	~States();

	void Initialize();

	void GetBaseRasterizerDesc(D3D11_RASTERIZER_DESC* desc);
	void GetBaseDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc);
	void GetBaseSamplerDesc(D3D11_SAMPLER_DESC* desc);
	void GetBaseBlendDesc(D3D11_BLEND_DESC* desc);

	void CreateRasterizerState(D3D11_RASTERIZER_DESC* desc, ID3D11RasterizerState** state);
	void CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC* desc, ID3D11DepthStencilState** state);
	void CreateSamplerState(D3D11_SAMPLER_DESC* desc, ID3D11SamplerState** state);
	void CreateBlendState(D3D11_BLEND_DESC* desc, ID3D11BlendState** state);

private:
	D3D11_RASTERIZER_DESC baseRasterizerDesc;
	D3D11_DEPTH_STENCIL_DESC baseDepthStencilDesc;
	D3D11_SAMPLER_DESC baseSamplerDesc;
	D3D11_BLEND_DESC baseBlendDesc;
};