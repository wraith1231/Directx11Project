#pragma once

//Base
#include <windows.h>
#include <assert.h>

//STL
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
using namespace std;

//Else
#include <Common.h>

//D3D
#include <dxgi1_2.h>
//#include <DXInc/DXGI.h>
#include <DXInc/D3Dcommon.h>
#include <DXInc/D3Dcompiler.h>
#include <DXInc/d3d11.h>
#include <DXInc/d3d11Shader.h>
#include <DXInc/d3dX10math.h>
#include <DXInc/d3dX11async.h>
#include <DXInc/DirectXTex.h>

#pragma comment(lib, "DXLib/dxgi.lib")
#pragma comment(lib, "DXLib/d3d11.lib")
#pragma comment(lib, "DXLib/d3dx9.lib")
#pragma comment(lib, "DXLib/d3dx10.lib")
#pragma comment(lib, "DXLib/d3dx11.lib")
#pragma comment(lib, "DXLib/d3dcompiler.lib")
#pragma comment(lib, "DXLib/dxguid.lib")
#pragma comment(lib, "DXLib/DirectXTex.lib")

/////////////////////////////////////////////////////////////////

//System Folder
#include "./System/Windows.h"
#include "./System/D3D.h"
#include "./System/InputManager.h"
#include "./System/TimeManager.h"

//Render Folder
#include "./Render/Shader.h"
#include "./Render/States.h"