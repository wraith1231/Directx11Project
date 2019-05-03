#include "stdafx.h"
#include "Windows.h"

Windows::Windows()
{
}

Windows::~Windows()
{
}

void Windows::Initialize(HINSTANCE instance)
{
	D3DDesc desc;
	Common::Singleton<D3D>::Get()->GetDesc(&desc);

	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hInstance = desc.Instance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = desc.AppName.c_str();
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);

	if (desc.FullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = (DWORD)desc.Width;
		devMode.dmPelsHeight = (DWORD)desc.Height;
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}

	desc.Handle = CreateWindowEx(WS_EX_APPWINDOW
		, desc.AppName.c_str()
		, desc.AppName.c_str()
		, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, CW_USEDEFAULT
		, NULL
		, (HMENU)NULL
		, desc.Instance
		, NULL);
	assert(desc.Handle != NULL);
	Common::Singleton<D3D>::Get()->SetDesc(desc);

	RECT rect = { 0, 0, (LONG)desc.Width, (LONG)desc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.Height) / 2;

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow(desc.Handle
		, centerX
		, centerY
		, rect.right - rect.left
		, rect.bottom - rect.top
		, TRUE);
	ShowWindow(desc.Handle, SW_SHOWNORMAL);
	SetForegroundWindow(desc.Handle);
	SetFocus(desc.Handle);

	ShowCursor(true);
}

void Windows::Clear()
{
	D3DDesc desc;
	Common::Singleton<D3D>::Get()->GetDesc(&desc);

	if (desc.FullScreen == true)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(desc.Handle);

	UnregisterClass(desc.AppName.c_str(), desc.Instance);
}

WPARAM Windows::Frame()
{
	MSG msg = { 0 };

	D3DDesc desc;
	Common::Singleton<D3D>::Get()->GetDesc(&desc);

	Common::Singleton<TimeManager>::Get()->Start();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Common::Singleton<TimeManager>::Get()->Frame();

			Common::Singleton<D3D>::Get()->Clear();

			Common::Singleton<D3D>::Get()->Present();
		}
	}

	return msg.wParam;
}

void Windows::Render()
{
}

LRESULT Windows::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Common::Singleton<InputManager>::Get()->InputProc(message, wParam, lParam);

	if (message == WM_SIZE)
	{
		float width = (float)LOWORD(lParam);
		float height = (float)HIWORD(lParam);

		Common::Singleton<D3D>::Get()->ResizeScreen(width, height);
	}

	if (message == WM_CLOSE || message == WM_DESTROY)
	{
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
