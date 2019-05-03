#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Constant Buffer
///////////////////////////////////////////////////////////////////////////////////////////////

enum SHADERBUFFERTYPE
{
	SHADER_NONE,
	SHADER_VERTEX,
	SHADER_DOMAIN,
	SHADER_HULL,
	SHADER_GEOMETRY,
	SHADER_COMPUTE,
	SHADER_PIXEL,
	SHADER_COUNT
};

class ShaderBuffer
{
public:
	void SetBuffer(UINT slot, SHADERBUFFERTYPE type);
	
protected:
	ShaderBuffer(void* data, UINT dataSize);
	virtual ~ShaderBuffer();

	void BufferCreate(bool useDesc = false, D3D11_BUFFER_DESC desc = { 0 });

private:
	void MapData(void* data, UINT dataSize);

	D3D11_BUFFER_DESC desc;
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;
};

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Base Class
///////////////////////////////////////////////////////////////////////////////////////////////

class Shader
{
public:
	Shader(wstring shaderFile);
	~Shader();

	wstring GetFile() { return shaderFile; }

	void Render();

	void CreateVertexShader(string vsName = "VS");
	void CreateHullShader(string hsName = "HS");
	void CreateDomainShader(string dsName = "DS");
	void CreateGeometryShader(string gsName = "GS");
	void CreateComputeShader(string csName = "CS");
	void CreatePixelShader(string psName = "PS");

	void CreateInputLayout();

	string GetVertexShaderName() { return vertexShaderName; }
	string GetHullShaderName() { return hullShaderName; }
	string GetDomainShaderName() { return domainShaderName; }
	string GetGeometryShaderName() { return geometryShaderName; }
	string GetComputeShaderName() { return computeShaderName; }
	string GetPixelShaderName() { return pixelShaderName; }

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error);

private:
	wstring shaderFile;
	string vertexShaderName;
	string hullShaderName;
	string domainShaderName;
	string geometryShaderName;
	string computeShaderName;
	string pixelShaderName;

	ID3D11VertexShader* vertexShader;
	ID3D11HullShader* hullShader;
	ID3D11DomainShader* domainShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11ComputeShader* computeShader;
	ID3D11PixelShader* pixelShader;

	ID3D11InputLayout* inputLayout;

	ID3DBlob* vertexBlob;
	ID3DBlob* hullBlob;
	ID3DBlob* domainBlob;
	ID3DBlob* geometryBlob;
	ID3DBlob* computeBlob;
	ID3DBlob* pixelBlob;

	ID3D11ShaderReflection* reflection;
};

///////////////////////////////////////////////////////////////////////////////////////////////
// Shader Manager Class
///////////////////////////////////////////////////////////////////////////////////////////////

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void AddShader(wstring fileName = L"", string vsName = "", string hsName = "", string dsName = ""
		, string gsName = "", string csName = "", string psName = "");

	void Render(wstring fileName);

	//ALL SET SHADER NULL
	void ClearShader();
	void Clear();

private:
	map<wstring, Shader*> shaders;

};