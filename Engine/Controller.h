#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define COUNT 1000
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Controller {
	static IDirectInput8* m_directInput;
	static IDirectInputDevice8* m_pad;
	DIDEVCAPS capabilities;

	DIJOYSTATE2 state;
public:
	Controller();
	~Controller();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();
	bool Frame();

	bool IsButtonPressed() const;
	int getVX() const;
	int getVY() const;

private:
	bool ReadInput();

	static BOOL CALLBACK enumCallback(const DIDEVICEINSTANCE* instance, VOID* context);
};

