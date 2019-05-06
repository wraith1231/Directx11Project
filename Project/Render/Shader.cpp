#include "stdafx.h"
#include "Shader.h"

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Constant Buffer
///////////////////////////////////////////////////////////////////////////////////////////////

void ShaderBuffer::SetBuffer(UINT slot, SHADERBUFFERTYPE type)
{
	if (type > SHADER_NONE && type < SHADER_COUNT)
	{
		MapData(data, dataSize);

		D3D* d3d = Common::Singleton<D3D>::Get();
		switch (type)
		{
		case SHADER_VERTEX:
			d3d->GetDC()->VSSetConstantBuffers(slot, 1, &buffer);
			break;
		case SHADER_DOMAIN:
			d3d->GetDC()->DSSetConstantBuffers(slot, 1, &buffer);
			break;
		case SHADER_HULL:
			d3d->GetDC()->HSSetConstantBuffers(slot, 1, &buffer);
			break;
		case SHADER_GEOMETRY:
			d3d->GetDC()->GSSetConstantBuffers(slot, 1, &buffer);
			break;
		case SHADER_COMPUTE:
			d3d->GetDC()->CSSetConstantBuffers(slot, 1, &buffer);
			break;
		case SHADER_PIXEL:
			d3d->GetDC()->PSSetConstantBuffers(slot, 1, &buffer);
			break;
		default:
			break;
		}
	}
}

ShaderBuffer::ShaderBuffer(void * data, UINT dataSize)
	: data(data)
	, dataSize(dataSize)
{
	BufferCreate();
}

ShaderBuffer::~ShaderBuffer()
{
	buffer->Release();
}

void ShaderBuffer::BufferCreate(bool useDesc, D3D11_BUFFER_DESC desc)
{
	if (useDesc == false)
	{
		this->desc.Usage = D3D11_USAGE_DYNAMIC;
		this->desc.ByteWidth = dataSize;
		this->desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		this->desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		this->desc.MiscFlags = 0;
		this->desc.StructureByteStride = 0;
	}
	else
	{
		this->desc = desc;
	}

	HRESULT hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateBuffer(&(this->desc), NULL, &buffer);
	assert(SUCCEEDED(hr));
}

void ShaderBuffer::MapData(void * data, UINT dataSize)
{
	D3D11_MAPPED_SUBRESOURCE subResource;

	HRESULT hr = Common::Singleton<D3D>::Get()->GetDC()->Map(buffer
		, 0
		, D3D11_MAP_WRITE_DISCARD
		, 0
		, &subResource);
	assert(SUCCEEDED(hr));

	memcpy(subResource.pData, data, dataSize);

	Common::Singleton<D3D>::Get()->GetDC()->Unmap(buffer, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Base Class
///////////////////////////////////////////////////////////////////////////////////////////////

Shader::Shader(wstring shaderFile)
	: shaderFile(shaderFile)
	, inputLayout(NULL)
	, vertexBlob(NULL), vertexShader(NULL)
	, hullBlob(NULL), hullShader(NULL)
	, domainBlob(NULL), domainShader(NULL)
	, geometryBlob(NULL), geometryShader(NULL)
	, computeBlob(NULL), computeShader(NULL)
	, pixelBlob(NULL), pixelShader(NULL)
	, vertexShaderName("")
	, hullShaderName("")
	, domainShaderName("")
	, geometryShaderName("")
	, computeShaderName("")
	, pixelShaderName("")
{
}

Shader::~Shader()
{
	reflection->Release();

	inputLayout->Release();

	//pixel
	if (pixelBlob != NULL)
	{
		pixelBlob->Release();
	}
	if (pixelShader != NULL)
	{
		pixelShader->Release();
	}

	//compute
	if (computeBlob != NULL)
	{
		computeBlob->Release();
	}
	if (computeShader != NULL)
	{
		computeShader->Release();
	}

	//geometry
	if (geometryBlob != NULL)
	{
		geometryBlob->Release();
	}
	if (geometryShader != NULL)
	{
		geometryShader->Release();
	}

	//domain
	if (domainBlob != NULL)
	{
		domainBlob->Release();
	}
	if (domainShader != NULL)
	{
		domainShader->Release();
	}
	
	//hull
	if (hullBlob != NULL)
	{
		hullBlob->Release();
	}
	if (hullShader != NULL)
	{
		hullShader->Release();
	}

	//vertex
	if (vertexBlob != NULL)
	{
		vertexBlob->Release();
	}
	if (vertexShader != NULL)
	{
		vertexShader->Release();
	}
}

void Shader::Render()
{
	D3D* d3d = Common::Singleton<D3D>::Get();

	d3d->GetDC()->IASetInputLayout(inputLayout);

	if (vertexShader != NULL)
		d3d->GetDC()->VSSetShader(vertexShader, NULL, 0);
	if (hullShader != NULL)
		d3d->GetDC()->HSSetShader(hullShader, NULL, 0);
	if (domainShader != NULL)
		d3d->GetDC()->DSSetShader(domainShader, NULL, 0);
	if (geometryShader != NULL)
		d3d->GetDC()->GSSetShader(geometryShader, NULL, 0);
	if (computeShader != NULL)
		d3d->GetDC()->CSSetShader(computeShader, NULL, 0);
	if (pixelShader != NULL)
		d3d->GetDC()->PSSetShader(pixelShader, NULL, 0);
}

void Shader::CreateVertexShader(string vsName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, vsName.c_str()
		, "vs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &vertexBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateVertexShader( vertexBlob->GetBufferPointer()
		, vertexBlob->GetBufferSize()
		, NULL
		, &vertexShader );
	assert(SUCCEEDED(hr));

	vertexShaderName = vsName;
}

void Shader::CreateHullShader(string hsName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, hsName.c_str()
		, "hs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &hullBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateHullShader(hullBlob->GetBufferPointer()
		, hullBlob->GetBufferSize()
		, NULL
		, &hullShader);
	assert(SUCCEEDED(hr));

	hullShaderName = hsName;
}

void Shader::CreateDomainShader(string dsName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, dsName.c_str()
		, "ds_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &domainBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateDomainShader(domainBlob->GetBufferPointer()
		, domainBlob->GetBufferSize()
		, NULL
		, &domainShader);
	assert(SUCCEEDED(hr));

	domainShaderName = dsName;
}

void Shader::CreateGeometryShader(string gsName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, gsName.c_str()
		, "gs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &geometryBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateGeometryShader(geometryBlob->GetBufferPointer()
		, geometryBlob->GetBufferSize()
		, NULL
		, &geometryShader);
	assert(SUCCEEDED(hr));

	geometryShaderName = gsName;
}

void Shader::CreateComputeShader(string csName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, csName.c_str()
		, "cs_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &computeBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateComputeShader(computeBlob->GetBufferPointer()
		, computeBlob->GetBufferSize()
		, NULL
		, &computeShader);
	assert(SUCCEEDED(hr));

	computeShaderName = csName;
}

void Shader::CreatePixelShader(string psName)
{
	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFile(shaderFile.c_str()
		, NULL, NULL
		, psName.c_str()
		, "ps_5_0"
		, D3D10_SHADER_ENABLE_STRICTNESS
		, 0, NULL
		, &pixelBlob
		, &error
		, NULL);
	CheckShaderError(hr, error);

	hr = Common::Singleton<D3D>::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer()
		, pixelBlob->GetBufferSize()
		, NULL
		, &pixelShader);
	assert(SUCCEEDED(hr));

	pixelShaderName = psName;
}

void Shader::CheckShaderError(HRESULT hr, ID3DBlob * error)
{
	if (FAILED(hr))
	{
		if (error != NULL)
		{
			string str = (const char *)error->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);
		}
		assert(false);
	}
}

void Shader::CreateInputLayout()
{
	ID3DBlob* blob;
	if (vertexBlob != NULL)
		blob = vertexBlob;
	else if (hullBlob != NULL)
		blob = hullBlob;
	else if (domainBlob != NULL)
		blob = domainBlob;
	else if (geometryBlob != NULL)
		blob = geometryBlob;
	else if (computeBlob != NULL)
		blob = computeBlob;
	else if (pixelBlob != NULL)
		blob = pixelBlob;
	else
		return;

	HRESULT hr;
	hr = D3DReflect(blob->GetBufferPointer()
		, blob->GetBufferSize()
		, IID_ID3D11ShaderReflection
		, (void**)&reflection);
	assert(SUCCEEDED(hr));

	D3D11_SHADER_DESC shaderDesc;
	reflection->GetDesc(&shaderDesc);

	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (UINT i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		reflection->GetInputParameterDesc(i, &paramDesc);

		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

		if (elementDesc.SemanticName[0] != 'I')
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		else
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
		elementDesc.InstanceDataStepRate = 0;

		if(paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		string temp = paramDesc.SemanticName;
		if (temp == "POSITION")
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		inputLayoutDesc.push_back(elementDesc);
	}

	if (inputLayoutDesc.size() > 0)
	{
		hr = Common::Singleton<D3D>::Get()->GetDevice()->CreateInputLayout(&inputLayoutDesc[0]
			, inputLayoutDesc.size()
			, blob->GetBufferPointer()
			, blob->GetBufferSize()
			, &inputLayout);
		assert(SUCCEEDED(hr));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Manager Class
///////////////////////////////////////////////////////////////////////////////////////////////

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	ClearShader();
	Clear();
}

void ShaderManager::AddShader(wstring fileName, string vsName, string hsName, string dsName, string gsName, string csName, string psName)
{
	if (fileName.length() < 1) return;

	map<wstring, Shader*>::iterator iter = shaders.find(fileName);
	if (iter != shaders.end())
	{
		return;
	}

	Shader* shader = new Shader(fileName);
	if (vsName != "")
		shader->CreateVertexShader(vsName);
	if (hsName != "")
		shader->CreateHullShader(hsName);
	if (dsName != "")
		shader->CreateDomainShader(dsName);
	if (gsName != "")
		shader->CreateGeometryShader(gsName);
	if (csName != "")
		shader->CreateComputeShader(csName);
	if (psName != "")
		shader->CreatePixelShader(psName);
	
	shader->CreateInputLayout();

	shaders[fileName] = shader;
}

void ShaderManager::AddShaderProcess(wstring fileName, ShaderManagingType type, string name)
{
	if (fileName.length() < 1)
		return;

	map<wstring, Shader*>::iterator iter = shaders.find(fileName);
	if (iter == shaders.end())
		return;

	switch (type)
	{
	case SHADER_MANAGE_VERTEX:
		(iter->second)->CreateVertexShader(name);
		break;
	case SHADER_MANAGE_HULL:
		(iter->second)->CreateHullShader(name);
		break;
	case SHADER_MANAGE_DOMAIN:
		(iter->second)->CreateDomainShader(name);
		break;
	case SHADER_MANAGE_GEOMETRY:
		(iter->second)->CreateGeometryShader(name);
		break;
	case SHADER_MANAGE_COMPUTE:
		(iter->second)->CreateComputeShader(name);
		break;
	case SHADER_MANAGE_PIXEL:
		(iter->second)->CreatePixelShader(name);
		break;
	default:
		break;
	}
}

void ShaderManager::Render(wstring fileName)
{
	map<wstring, Shader*>::iterator iter = shaders.find(fileName);
	if (iter == shaders.end())
		return;

	(iter->second)->Render();
}

void ShaderManager::ClearShader()
{
	D3D* d3d = Common::Singleton<D3D>::Get();

	d3d->GetDC()->VSSetShader(NULL, NULL, 0);
	d3d->GetDC()->HSSetShader(NULL, NULL, 0);
	d3d->GetDC()->DSSetShader(NULL, NULL, 0);
	d3d->GetDC()->GSSetShader(NULL, NULL, 0);
	d3d->GetDC()->CSSetShader(NULL, NULL, 0);
	d3d->GetDC()->PSSetShader(NULL, NULL, 0);
}

void ShaderManager::Clear()
{
	map<wstring, Shader*>::iterator iter;
	for (iter = shaders.begin(); iter != shaders.end(); ++iter)
	{
		delete iter->second;
	}
	shaders.clear();
}
