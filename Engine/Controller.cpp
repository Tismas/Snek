#include "Controller.h"



Controller::Controller() {
	for (int i = 0; i < MAX_PADS; ++i)
		states[i] = { 0 };
}


Controller::~Controller() {
	Shutdown();
}

IDirectInput8* Controller::m_directInput = 0;
IDirectInputDevice8* Controller::m_pads[MAX_PADS] = { 0 };
int Controller::padsNum = 0;

BOOL CALLBACK
Controller::enumCallback(const DIDEVICEINSTANCE* instance, VOID* context) {
	HRESULT hr;

	// Obtain an interface to the enumerated joystick.
	hr = m_directInput->CreateDevice(instance->guidInstance, &m_pads[padsNum++], NULL);

	// If it failed, then we can't use this joystick. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(hr)) {
		return DIENUM_CONTINUE;
	}

	// Stop enumeration. Note: we're just taking the first joystick we get. You
	// could store all the enumerated joysticks and let the user pick.
	// return DIENUM_STOP;
	return DIENUM_CONTINUE;
}

bool Controller::Initialize(HINSTANCE hinstance, HWND hwnd) {
	HRESULT result;
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result)) return false;

	result = m_directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, enumCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(result)) return false;

	for (int i = 0; i < padsNum; ++i) {
		result = m_pads[i]->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(result)) return false;

		result = m_pads[i]->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(result)) return false;

		result = m_pads[i]->Acquire();
		if (FAILED(result)) return false;
	}
	return true;
}

void Controller::Shutdown() {
	for (int i = 0; i < padsNum; ++i) {
		if (m_pads[i]) {
			m_pads[i]->Unacquire();
			m_pads[i]->Release();
			m_pads[i] = 0;
		}
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

int Controller::getVX(int padInd) const {
	if (states[padInd].lX - 32767 > 10000) {
		return 1;
	}
	else if (states[padInd].lX - 32767 < -10000) {
		return -1;
	}
	return 0;
}

int Controller::getVY(int padInd) const {
	if (states[padInd].lY - 32767 > 10000) {
		return 1;
	}
	else if (states[padInd].lY - 32767 < -10000) {
		return -1;
	}
	return 0;
}

bool Controller::ReadInput() {
	HRESULT result;


	for (int i = 0; i < padsNum; ++i) {
		result = m_pads[i]->Poll();
		if (FAILED(result)) {
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED)) {
				m_pads[i]->Acquire();
			}
			else {
				return false;
			}
		}
		if (FAILED(m_pads[i]->GetDeviceState(sizeof(DIJOYSTATE2), &states[i]))) return false;
	}
	return true;
}
