
#include "Engine.h"

/*------------------------------------------------------------------------------
Macross
------------------------------------------------------------------------------*/
#define CLASS_NAME _T("AppClass")
#define WINDOW_NAME _T("Vania")
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)


/*------------------------------------------------------------------------------
Prototype
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDirectX(HWND hWnd, BOOL bWindow);


/*------------------------------------------------------------------------------
Global variables
------------------------------------------------------------------------------*/
LPDIRECT3D9 gD3D = NULL;
LPDIRECT3DDEVICE9 gD3DDevice = NULL;


/*------------------------------------------------------------------------------
Global Object
------------------------------------------------------------------------------*/
Time* time = new Time();
Player* player = new Player();


/*------------------------------------------------------------------------------
Debug
------------------------------------------------------------------------------*/
#ifdef _DEBUG
	LPD3DXFONT gD3DXFont = NULL; // D3D font pointer

	void DrawDebugFont() {
		RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
		char str[256];
		sprintf(str,"FPS:%d\nDeltaTime:%.3fs\n", time->countFPS, time->deltaTime);
		gD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff,0xff,0xff,0xff));
	}
#endif

/*------------------------------------------------------------------------------
Start
------------------------------------------------------------------------------*/
void Start() {
	time->Start();
	player->Start();
}

/*------------------------------------------------------------------------------
Update
------------------------------------------------------------------------------*/
void Update(void) {
	UpdateInput();
	time->Update();
	player->Update();
}

/*------------------------------------------------------------------------------
Draw
------------------------------------------------------------------------------*/
void Draw(void) {
	gD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if(SUCCEEDED(gD3DDevice->BeginScene())) {

		player->Draw();

		#ifdef _DEBUG
			DrawDebugFont();
		#endif

		gD3DDevice->EndScene();
	}

	gD3DDevice->Present(NULL, NULL, NULL, NULL);
}


/*------------------------------------------------------------------------------
Delete
------------------------------------------------------------------------------*/
void Delete(void)
{
	if(gD3DDevice != NULL) {
		gD3DDevice->Release();
	}

	if(gD3D != NULL) {
		gD3D->Release();
	}

	#ifdef _DEBUG
		if(gD3DXFont != NULL) {
			gD3DXFont->Release();
		}
	#endif

	delete time;
	delete player;

	UninitInput();
}


/*------------------------------------------------------------------------------
main
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// ignore warning
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEX wcex = {
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
	HWND hWnd;
	MSG  msg;

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
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	/*------------------------------------------------------------------------------
	Start
	------------------------------------------------------------------------------*/
	Start();


	InitInput(hInstance,hWnd);

	while(1) {

		// check for break app
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {
				break;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}


		/*------------------------------------------------------------------------------
		Update
		------------------------------------------------------------------------------*/
		// set time
		time->SetTime();
		// Update
		if (time->CheckFPS(60)) {
			Update();
			Draw();
		}
	}


	/*------------------------------------------------------------------------------
	Delete
	------------------------------------------------------------------------------*/
	Delete();
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	return (int)msg.wParam;
}


/*------------------------------------------------------------------------------
Get gD3DDevice
------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice(void) {
	return(gD3DDevice);
}















LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_ESCAPE: // [ESC] key
					DestroyWindow(hWnd);
					break;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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


	#ifdef _DEBUG
		D3DXCreateFont(gD3DDevice,18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Terminal"),&gD3DXFont);
	#endif

	return S_OK;
}
