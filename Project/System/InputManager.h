#pragma once

#define MAX_INPUT_MOUSE 8
#define MAX_INPUT_KEYBOARD 255

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Frame();

	//Mouse
	LRESULT InputProc(UINT message, WPARAM wParam, LPARAM lParam);

	D3DXVECTOR3 GetMousePosition() { return mousePosition; }

	D3DXVECTOR3 GetWheelStatus() { return wheelStatus; }
	D3DXVECTOR3 GetWheelOldStatus() { return wheelOldStatus; }
	D3DXVECTOR3 GetWheelMoveValue() { return wheelMoveValue; }

	//Keyboard
	bool IsKeyDown(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool IsKeyUp(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool IsKeyPress(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }

private:
	HWND handle;
	D3DXVECTOR3 mousePosition;

	//Mouse
	D3DXVECTOR3 wheelStatus;
	D3DXVECTOR3 wheelOldStatus;
	D3DXVECTOR3 wheelMoveValue;

	enum
	{
		MOUSE_ROTATION_NONE = 0,
		MOUSE_ROTATION_LEFT,
		MOUSE_ROTATION_RIGHT
	};

	enum
	{
		BUTTON_INPUT_STATUS_NONE = 0,
		BUTTON_INPUT_STATUS_DOWN,
		BUTTON_INPUT_STATUS_UP,
		BUTTON_INPUT_STATUS_PRESS,
		BUTTON_INPUT_STATUS_DOUBLE
	};

	//Keyboard
	byte keyState[MAX_INPUT_KEYBOARD];
	byte keyOldState[MAX_INPUT_KEYBOARD];
	byte keyMap[MAX_INPUT_KEYBOARD];

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};

};