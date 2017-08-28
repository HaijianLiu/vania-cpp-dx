
#include "Engine.h"

/*------------------------------------------------------------------------------
Global variables
------------------------------------------------------------------------------*/
LPDIRECT3D9 gD3D = NULL;
LPDIRECT3DDEVICE9 gD3DDevice = NULL;
IDirectSound8* gDirectSound = NULL;
HWND hWnd;
MSG  msg;
WNDCLASSEX wcex;

/*------------------------------------------------------------------------------
Functions
------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice() {
	return gD3DDevice;
}
IDirectSound8* GetDirectSound() {
	return gDirectSound;
}


void ClearWindow() {
	gD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
}

bool WindowBeginScene() {
	return SUCCEEDED(gD3DDevice->BeginScene());
}
void WindowEndScene() {
	gD3DDevice->EndScene();
}

void PresentWindow() {
	gD3DDevice->Present(NULL, NULL, NULL, NULL);
}

int DeleteWindow() {
	if (gDirectSound != NULL) gDirectSound->Release();
	if (gD3DDevice != NULL) gD3DDevice->Release();
	if (gD3D != NULL) gD3D->Release();
	UninitInput();
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;
}

bool InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// ignore warning
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// Register window Class Ex
	RegisterClassEx(&wcex);

	// Create Window
	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		hInstance,
		NULL);

	// Init DirectX
	if(FAILED(InitDirectX(hWnd, true))) {
		return false;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	InitInput(hInstance,hWnd);
	InitSound(hWnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					break;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

bool CheckBreak() {
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if(msg.message == WM_QUIT) {
			return true;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return false;
}



HRESULT InitDirectX(HWND hWnd, BOOL bWindow) {
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Create Direct3D Object
	gD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(gD3D == NULL) {
		return E_FAIL;
	}

	// Get Adapter Display Mode
	if(FAILED(gD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// Display Parameters
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = bWindow;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	if(bWindow) {
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else {
		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// Create device
	if(FAILED(gD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &gD3DDevice))) {
		if(FAILED(gD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &gD3DDevice))) {
			if(FAILED(gD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &gD3DDevice))) {
				return E_FAIL;
			}
		}
	}

	// Set Render State
	gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	gD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	gD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	gD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	gD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Set Sampler State
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	gD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	gD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	gD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	gD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	return S_OK;
}

HRESULT InitSound(HWND hWnd) {
	// Create DirectSound
	if (FAILED(DirectSoundCreate8(NULL, &gDirectSound, NULL))) return E_FAIL;

	// Set Cooperative Level
	if (FAILED(gDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY))) return E_FAIL;

	return S_OK;
}
