
#include "Engine.h"

/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/
#define	NUM_KEY_MAX (256)

/*------------------------------------------------------------------------------
< Pravite Functions Prototype >
------------------------------------------------------------------------------*/
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

/*------------------------------------------------------------------------------
< Globals >
------------------------------------------------------------------------------*/
LPDIRECTINPUT8 gDInput = NULL;
LPDIRECTINPUTDEVICE8 gDIDevKeyboard = NULL;
BYTE gKeyState[NUM_KEY_MAX];
BYTE gKeyStateTrigger[NUM_KEY_MAX];
BYTE gKeyStateRepeat[NUM_KEY_MAX];
BYTE gKeyStateRelease[NUM_KEY_MAX];
int gKeyStateRepeatCnt[NUM_KEY_MAX];


/*------------------------------------------------------------------------------
< Public Functions >
------------------------------------------------------------------------------*/
HRESULT InitInput(HINSTANCE hInst, HWND hWnd) {
	HRESULT hr;
	// Create DirectInput8 Object
	if(!gDInput) {
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&gDInput, NULL);
	}
	// Init keyboard
	InitKeyboard(hInst, hWnd);
	return hr;
}

void UninitInput(void) {
	UninitKeyboard();
	if(gDInput) {
		gDInput->Release();
		gDInput = NULL;
	}
}

void UpdateInput(void) {
	UpdateKeyboard();
}


bool GetKeyboardPress(int key) {
	return (gKeyState[key] & 0x80) ? true : false;
}
bool GetKeyboardTrigger(int key) {
	return (gKeyStateTrigger[key] & 0x80) ? true : false;
}
bool GetKeyboardRepeat(int key) {
	return (gKeyStateRepeat[key] & 0x80) ? true : false;
}
bool GetKeyboardRelease(int key) {
	return (gKeyStateRelease[key] & 0x80) ? true : false;
}


/*------------------------------------------------------------------------------
< Keyboard Functions >
------------------------------------------------------------------------------*/
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd) {
	HRESULT hr;
	// Create Keyboard LPDIRECTINPUTDEVICE8 Device
	hr = gDInput->CreateDevice(GUID_SysKeyboard, &gDIDevKeyboard, NULL);
	if(FAILED(hr) || gDIDevKeyboard == NULL) {
		MessageBox(hWnd, _T("FAILED TO CREATE KEYBOARD DEVICE"), _T("WARNING"), MB_ICONWARNING);
		return hr;
	}
	// Set Data Format
	hr = gDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr)) {
		MessageBox(hWnd, _T("FAILED TO SET KEYBOARD DATA FORMAT"), _T("WARNING"), MB_ICONWARNING);
		return hr;
	}
	// Set Cooperative Level
	hr = gDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr)) {
		MessageBox(hWnd, _T("FAILED TO SET KEYBOARD COOPERATIVE LEVEL"), _T("WARNING"), MB_ICONWARNING);
		return hr;
	}
	// Acquire
	gDIDevKeyboard->Acquire();

	return S_OK;
}


void UninitKeyboard() {
	if(gDIDevKeyboard) {
		gDIDevKeyboard->Unacquire();
		gDIDevKeyboard->Release();
		gDIDevKeyboard = NULL;
	}
}


HRESULT UpdateKeyboard() {
	HRESULT hr;
	BYTE keyStateOld[NUM_KEY_MAX];

	memcpy(keyStateOld, gKeyState, NUM_KEY_MAX);

	hr = gDIDevKeyboard->GetDeviceState(sizeof(gKeyState), gKeyState);
	if(SUCCEEDED(hr)) {
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++) {
			gKeyStateTrigger[cnt] = (keyStateOld[cnt] ^ gKeyState[cnt]) & gKeyState[cnt];
			gKeyStateRelease[cnt] = (keyStateOld[cnt] ^ gKeyState[cnt]) & ~gKeyState[cnt];
			gKeyStateRepeat[cnt] = gKeyStateTrigger[cnt];
			if(gKeyState[cnt]) {
				gKeyStateRepeatCnt[cnt]++;
				if(gKeyStateRepeatCnt[cnt] >= 20) {
					gKeyStateRepeat[cnt] = gKeyState[cnt];
				}
			}
			else {
				gKeyStateRepeatCnt[cnt] = 0;
				gKeyStateRepeat[cnt] = 0;
			}
		}
	}
	else {
		hr = gDIDevKeyboard->Acquire();
	}

	return hr;
}
