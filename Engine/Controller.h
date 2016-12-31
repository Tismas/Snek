#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define COUNT 1000
#define MAX_PADS 4
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Controller {
	static int padsNum;
	static IDirectInput8* m_directInput;
	static IDirectInputDevice8* m_pads[MAX_PADS];

	DIJOYSTATE2 states[MAX_PADS];
public:
	Controller();
	~Controller();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();
	bool Frame();

	bool IsButtonPressed() const;
	int getVX(int padInd) const;
	int getVY(int padInd) const;

private:
	bool ReadInput();

	static BOOL CALLBACK enumCallback(const DIDEVICEINSTANCE* instance, VOID* context);
};

