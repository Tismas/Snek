#include "Controller.h"



Controller::Controller() {
	state = { 0 };
}


Controller::~Controller() {
	if (m_pad) {
		m_pad->Unacquire();
	}
}

IDirectInput8* Controller::m_directInput = 0;
IDirectInputDevice8* Controller::m_pad = 0;
BOOL CALLBACK
Controller::enumCallback(const DIDEVICEINSTANCE* instance, VOID* context) {
	HRESULT hr;

	// Obtain an interface to the enumerated joystick.
	hr = m_directInput->CreateDevice(instance->guidInstance, &m_pad, NULL);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	return DIENUM_STOP;
}

bool Controller::Initialize(HINSTANCE hinstance, HWND hwnd) {
	HRESULT result;
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)) return false;

	result = m_directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(result)) return false;

	result = m_pad->SetDataFormat(&c_dfDIJoystick2);
	if (FAILED(result)) return false;

	result = m_pad->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result)) return false;

	result = m_pad->Acquire();
	if (FAILED(result)) return false;

	capabilities.dwSize = sizeof(DIDEVCAPS);
	if (FAILED(m_pad->GetCapabilities(&capabilities))) return false;

	return true;
}

void Controller::Shutdown() {
	if (m_pad) {
		m_pad->Unacquire();
		m_pad->Release();
		m_pad = 0;
	}
	if (m_directInput) {
		m_directInput->Release();
		m_directInput = 0;
	}
}

bool Controller::Frame() {
	bool result;

	result = ReadInput();
	if (!result) return false;

	return true;
}

bool Controller::IsButtonPressed() const {
	return false;
}

int Controller::getVX() const {
	if (state.lX - 32767 > 10000) {
		return 1;
	}
	else if (state.lX - 32767 < -10000) {
		return -1;
	}
	return 0;
}

int Controller::getVY() const {
	if (state.lY - 32767 > 10000) {
		return 1;
	}
	else if (state.lY - 32767 < -10000) {
		return -1;
	}
	return 0;
}

bool Controller::ReadInput() {
	HRESULT result;

	result = m_pad->Poll();
	if (FAILED(result)) {
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
			m_pad->Acquire();
		}
		else {
			return false;
		}
	}
	if (FAILED(m_pad->GetDeviceState(sizeof(DIJOYSTATE2), &state))) return false;
	return true;
}
