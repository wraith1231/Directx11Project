#pragma once

struct D3DDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	float Width;
	float Height;
	bool Vsync;
	bool FullScreen;
};

class D3D
{
public:
	D3D();
	~D3D();

	void Initialize();

	void SetGpuInfo();
	void CreateSwapChainAndDevice();

	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

	void SetRenderTarget(ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL);
	void Clear(D3DXCOLOR color = D3DXCOLOR(0xFF555566), ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL);
	void Present();

	void ResizeScreen(float width, float height);

	void GetDesc(D3DDesc* desc)
	{
		*desc = d3dDesc;
	}

	void SetDesc(D3DDesc& desc)
	{
		d3dDesc = desc;
	}

	ID3D11Device* GetDevice()
	{
		return device;
	}
	ID3D11DeviceContext* GetDC()
	{
		return deviceContext;
	}

	IDXGISwapChain* GetSwapChain()
	{
		return swapChain;
	}

	ID3D11ShaderResourceView* GetSRC()
	{
		return srv;
	}

	ID3D11DepthStencilView* GetDSV()
	{
		return depthStencilView;
	}
	ID3D11DepthStencilView* GetReadOnlyDSV()
	{
		return readOnlyDSV;
	}

	ID3D11DepthStencilState* GetDSS()
	{
		return dss;	
	}

private:
	D3DDesc d3dDesc;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11ShaderResourceView* srv;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11DepthStencilView* readOnlyDSV;
	ID3D11DepthStencilState* dss;

	ID3D11Texture2D* backBuffer;
	ID3D11RenderTargetView* mainRTV;

	ID3D11Debug* debugDevice;

	UINT gpuMemorySize;
	wstring gpuDescription;

	UINT numerator;
	UINT denominator;

};