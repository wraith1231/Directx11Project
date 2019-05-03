#include "stdafx.h"
#include "D3D.h"

D3D::D3D()
	: numerator(0), denominator(1)
{
}

D3D::~D3D()
{
	DeleteBackBuffer();

	if (swapChain != NULL)
		swapChain->SetFullscreenState(false, NULL);

	srv->Release();
	dss->Release();
	deviceContext->Release();
	device->Release();
	swapChain->Release();
}

void D3D::Initialize()
{
	SetGpuInfo();

	CreateSwapChainAndDevice();
	CreateBackBuffer(d3dDesc.Width, d3dDesc.Height);
}

void D3D::SetGpuInfo()
{
	HRESULT hr;

	IDXGIFactory* factory;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	assert(SUCCEEDED(hr));

	IDXGIAdapter* adapter;
	hr = factory->EnumAdapters(0, &adapter);
	assert(SUCCEEDED(hr));

	IDXGIOutput* adapterOutput;
	hr = adapter->EnumOutputs(0, &adapterOutput);
	assert(SUCCEEDED(hr));

	UINT modeCount;
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		NULL);
	assert(SUCCEEDED(hr));

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[modeCount];
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&modeCount,
		displayModeList);
	assert(SUCCEEDED(hr));

	for (UINT i = 0; i < modeCount; i++)
	{
		bool isCheck = true;
		isCheck &= displayModeList[i].Width == d3dDesc.Width;
		isCheck &= displayModeList[i].Height == d3dDesc.Height;

		if (isCheck == true)
		{
			numerator = displayModeList[i].RefreshRate.Numerator;
			denominator = displayModeList[i].RefreshRate.Denominator;
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	hr = adapter->GetDesc(&adapterDesc);
	assert(SUCCEEDED(hr));

	gpuMemorySize = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	gpuDescription = adapterDesc.Description;

	delete[] displayModeList;

	adapterOutput->Release();
	adapter->Release();
	factory->Release();
}

void D3D::CreateSwapChainAndDevice()
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (d3dDesc.Vsync == true)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = d3dDesc.Handle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !d3dDesc.FullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&swapChain,
		&device,
		NULL,
		&deviceContext);
	assert(SUCCEEDED(hr));
}

void D3D::CreateBackBuffer(float width, float height)
{
	HRESULT hr;

	if (width <= 0 || height <= 0) return;

	{
		D3D11_TEXTURE2D_DESC desc = { 0 };
		desc.Width = (UINT)width;
		desc.Height = (UINT)height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		hr = device->CreateTexture2D(&desc, NULL, &backBuffer);
		assert(SUCCEEDED(hr));
	}

	{
		ID3D11Texture2D* backBufferPointer;
		hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferPointer);
		assert(SUCCEEDED(hr));

		hr = device->CreateRenderTargetView(backBufferPointer, NULL, &mainRTV);
		assert(SUCCEEDED(hr));

		backBufferPointer->Release();
	}

	{
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		hr = device->CreateDepthStencilView(backBuffer, &dsvDesc, &depthStencilView);
		assert(SUCCEEDED(hr));
		dsvDesc.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;
		hr = device->CreateDepthStencilView(backBuffer, &dsvDesc, &readOnlyDSV);
		assert(SUCCEEDED(hr));

		SetRenderTarget(mainRTV, depthStencilView);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;

		hr = device->CreateShaderResourceView(backBuffer, &srvDesc, &srv);
		assert(SUCCEEDED(hr));

		D3D11_DEPTH_STENCIL_DESC dsDesc;
		dsDesc.DepthEnable = true;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		dsDesc.StencilEnable = true;
		dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		D3D11_DEPTH_STENCILOP_DESC dsopDesc = { D3D11_STENCIL_OP_REPLACE,
		D3D11_STENCIL_OP_REPLACE,
		D3D11_STENCIL_OP_REPLACE,
		D3D11_COMPARISON_ALWAYS };
		dsDesc.FrontFace = dsopDesc;
		dsDesc.BackFace = dsopDesc;

		hr = device->CreateDepthStencilState(&dsDesc, &dss);
		assert(SUCCEEDED(hr));
	}
}

void D3D::DeleteBackBuffer()
{
	depthStencilView->Release();
	mainRTV->Release();
	backBuffer->Release();
}

void D3D::SetRenderTarget(ID3D11RenderTargetView * rtv, ID3D11DepthStencilView * dsv)
{
	if (rtv == NULL)
		rtv = mainRTV;

	if (dsv == NULL)
		dsv = depthStencilView;

	deviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void D3D::Clear(D3DXCOLOR color, ID3D11RenderTargetView * rtv, ID3D11DepthStencilView * dsv)
{
	if (rtv == NULL)
		rtv = mainRTV;
	if (dsv == NULL)
		dsv = depthStencilView;

	deviceContext->ClearRenderTargetView(rtv, color);
	deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
}

void D3D::Present()
{
	swapChain->Present(d3dDesc.Vsync == true ? 1 : 0, 0);
}

void D3D::ResizeScreen(float width, float height)
{
	d3dDesc.Width = width;
	d3dDesc.Height = height;

	DeleteBackBuffer();
	{
		HRESULT hr = swapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
		assert(SUCCEEDED(hr));
	}

	CreateBackBuffer(width, height);
}
