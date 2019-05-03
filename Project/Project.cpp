// Project.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

void SetSingleton()
{
	Common::Singleton<D3D>::Set(new D3D());
	Common::Singleton<InputManager>::Set(new InputManager());
	Common::Singleton<TimeManager>::Set(new TimeManager());
	Common::Singleton<ShaderManager>::Set(new ShaderManager());
	Common::Singleton<States>::Set(new States());
}

void DestroySingleton()
{
	Common::Singleton<States>::Destroy();
	Common::Singleton<ShaderManager>::Destroy();
	Common::Singleton<TimeManager>::Destroy();
	Common::Singleton<InputManager>::Destroy();
	Common::Singleton<D3D>::Destroy();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetSingleton();

	Common::Singleton<D3D>::Get()->Initialize();
	Common::Singleton<States>::Get()->Initialize();
	
	Windows* windows = new Windows();

	windows->Initialize(hInstance);

	windows->Frame();

	windows->Clear();

	DestroySingleton();

	delete windows;

	return 0;
}