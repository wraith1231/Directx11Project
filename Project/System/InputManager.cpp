#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
	//Mouse
	mousePosition = D3DXVECTOR3(0, 0, 0);

	wheelStatus = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	wheelOldStatus = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	wheelMoveValue = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	DWORD tLine = 0;
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &tLine, 0);

	//Keyboard
	ZeroMemory(keyState, sizeof(byte) * MAX_INPUT_KEYBOARD);
	ZeroMemory(keyOldState, sizeof(byte) * MAX_INPUT_KEYBOARD);
	ZeroMemory(keyMap, sizeof(byte) * MAX_INPUT_KEYBOARD);
}

InputManager::~InputManager()
{
}

void InputManager::Frame()
{
	//Mouse(wheel only)
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(handle, &point);

	wheelOldStatus = wheelStatus;
	wheelStatus = D3DXVECTOR3((float)point.x, (float)point.y, wheelStatus.z);

	wheelMoveValue = wheelStatus - wheelOldStatus;
	wheelOldStatus.z = wheelStatus.z;

	//Keyboard
	memcpy(keyOldState, keyState, sizeof(byte) * MAX_INPUT_KEYBOARD);

	ZeroMemory(keyState, sizeof(byte) * MAX_INPUT_KEYBOARD);
	ZeroMemory(keyMap, sizeof(byte) * MAX_INPUT_KEYBOARD);

	GetKeyboardState(keyState);

	for (DWORD i = 0; i < MAX_INPUT_KEYBOARD; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int oldState = keyOldState[i];
		int state = keyState[i];

		if (oldState == 0 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_DOWN;
		else if (oldState == 1 && state == 0)
			keyMap[i] = KEY_INPUT_STATUS_UP;
		else if (oldState == 1 && state == 1)
			keyMap[i] = KEY_INPUT_STATUS_PRESS;
		else
			keyMap[i] = KEY_INPUT_STATUS_NONE;
	}
}

LRESULT InputManager::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN || message == WM_MOUSEMOVE)
	{
		mousePosition.x = (float)LOWORD(lParam);
		mousePosition.y = (float)HIWORD(lParam);
	}

	if (message == RI_MOUSE_WHEEL)
	{
		short tWheelValue = (short)HIWORD(wParam);

		wheelOldStatus.z = wheelStatus.z;
		wheelStatus.z += (float)tWheelValue;
	}

	return TRUE;
}
