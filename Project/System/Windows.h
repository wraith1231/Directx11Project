#pragma once

class Windows
{
public:
	Windows();
	~Windows();

	void Initialize(HINSTANCE instance);
	void Clear();
	WPARAM Frame();
	void Render();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

private:

};