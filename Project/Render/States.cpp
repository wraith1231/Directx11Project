#include "stdafx.h"
#include "States.h"

States::States()
{
	ZeroMemory(&baseRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	ZeroMemory(&baseDepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	ZeroMemory(&baseSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	ZeroMemory(&baseBlendDesc, sizeof(D3D11_BLEND_DESC));
}

States::~States()
{
}

void States::Initialize()
{
	//rasterizer
	{
		baseRasterizerDesc.AntialiasedLineEnable = false;
		baseRasterizerDesc.CullMode = D3D11_CULL_BACK;
		baseRasterizerDesc.DepthBias = 0;
		baseRasterizerDesc.DepthBiasClamp = 0.0f;
		baseRasterizerDesc.DepthClipEnable = true;
		baseRasterizerDesc.FillMode = D3D11_FILL_SOLID;
		baseRasterizerDesc.FrontCounterClockwise = false;
		baseRasterizerDesc.MultisampleEnable = false;
		baseRasterizerDesc.ScissorEnable = false;
		baseRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	}

	//depth stencil
	{
		baseDepthStencilDesc.DepthEnable = true;
		baseDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		baseDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		baseDepthStencilDesc.StencilEnable = true;
		baseDepthStencilDesc.StencilReadMask = 0xFF;
		baseDepthStencilDesc.StencilWriteMask = 0xFF;

		baseDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		baseDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		baseDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		baseDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		baseDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		baseDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		baseDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		baseDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	}

	//sampler
	{
		baseSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		baseSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		baseSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		baseSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		baseSamplerDesc.MaxAnisotropy = 1;
		baseSamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		baseSamplerDesc.MinLOD = 0;
		baseSamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	}

	//blend
	{
		baseBlendDesc.AlphaToCoverageEnable = false;
		baseBlendDesc.IndependentBlendEnable = false;

		baseBlendDesc.RenderTarget[0].BlendEnable = false;
		baseBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		baseBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		baseBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		baseBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		baseBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		baseBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		baseBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
}

void States::GetBaseRasterizerDesc(D3D11_RASTERIZER_DESC * desc)
{
	memcpy(desc, &baseRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
}

void States::GetBaseDepthStencilDesc(D3D11_DEPTH_STENCIL_DESC* desc)
{
	memcpy(desc, &baseDepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
}

void States::GetBaseSamplerDesc(D3D11_SAMPLER_DESC * desc)
{
	memcpy(desc, &baseSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
}

void States::GetBaseBlendDesc(D3D11_BLEND_DESC * desc)
{
	memcpy(desc, &baseBlendDesc, sizeof(D3D11_BLEND_DESC));
}

void States::CreateRasterizerState(D3D11_RASTERIZER_DESC * desc, ID3D11RasterizerState ** state)
{
	HRESULT hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateRasterizerState(desc, state);
	assert(SUCCEEDED(hr));
}

void States::CreateDepthStencilState(D3D11_DEPTH_STENCIL_DESC * desc, ID3D11DepthStencilState ** state)
{
	HRESULT hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateDepthStencilState(desc, state);
	assert(SUCCEEDED(hr));
}

void States::CreateSamplerState(D3D11_SAMPLER_DESC * desc, ID3D11SamplerState ** state)
{
	HRESULT hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateSamplerState(desc, state);
	assert(SUCCEEDED(hr));
}

void States::CreateBlendState(D3D11_BLEND_DESC * desc, ID3D11BlendState ** state)
{
	HRESULT hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateBlendState(desc, state);
	assert(SUCCEEDED(hr));
}
