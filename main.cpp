
#define _CRT_SECURE_NO_WARNINGS // scanf のwarning防止
#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>

#define DIRECTINPUT_VERSION 0x0800 // 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1 // [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

#define SCREEN_WIDTH    (640)                 // ウインドウの幅
#define SCREEN_HEIGHT   (480)                 // ウインドウの高さ
#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)   // ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)   // ウインドウの中心Ｙ座標

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct {
	D3DXVECTOR3 vtx;  // 頂点座標
	float rhw;        // テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse; // 反射光
	D3DXVECTOR2 tex;  // テクスチャ座標(*33)
} VERTEX_2D;


LPDIRECT3DDEVICE9 GetDevice(void); // デバイス取得関数

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME  _T("AppClass")     // ウインドウのクラス名
#define WINDOW_NAME _T("vania") // ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HWND hWnd, BOOL bWindow);

void Update(void);
void Draw(void);
void Uninit(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9       g_pD3D = NULL;       // Direct3Dオブジェクト
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL; // Deviceオブジェクト(描画に必要)

#ifdef _DEBUG // (*35)
	LPD3DXFONT g_pD3DXFont = NULL; // フォントへのポインタ
	int        g_nCountFPS; // FPSカウンタ
	void       DrawDebugFont(void);
#endif


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//時間計測用 (*35)
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// window class
	WNDCLASSEX wcex = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, hInstance, NULL, LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW+1), NULL, CLASS_NAME, NULL};
	HWND hWnd;
	MSG  msg;
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // ウィンドウの左座標
		CW_USEDEFAULT, // ウィンドウの上座標
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2, // ウィンドウ横幅
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2 + GetSystemMetrics(SM_CYCAPTION), // ウィンドウ縦幅
		NULL, NULL, hInstance, NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hWnd, true))) {
		return -1;
	}

	// フレイムカウンタの初期化
	timeBeginPeriod(1); // 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime(); // ミリ秒単位で取特
	dwCurrentTime  = dwFrameCount  = 0;

	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// InitInput(hInstance,hWnd);

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) {// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else {
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500) {

				#ifdef _DEBUG
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime); // FPSを計測
				#endif

				dwFPSLastTime = dwCurrentTime; // FPS計測時刻を保存
				dwFrameCount = 0; // カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60)) { // 1/60秒ごとに実行
				dwExecLastTime = dwCurrentTime; // 処理した時刻を保存
				// 更新処理
				Update();
				// 描画処理
				Draw();
				dwFrameCount ++; // 処理回数のカウントを加算
			}
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE        d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL) {
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))) {
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // ワークをゼロクリア
	d3dpp.BackBufferCount        = 1; // バックバッファの数
	d3dpp.BackBufferWidth        = SCREEN_WIDTH; // ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight       = SCREEN_HEIGHT; // ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN; // バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD; // 映像信号に同期してフリップする
	d3dpp.Windowed               = bWindow; // ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE; // デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16; // デプスバッファとして16bitを使う
	d3dpp.BackBufferFormat       = d3ddm.Format; // カラーモードの指定

	if(bWindow) { // ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN; // バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0; // リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; // インターバル
	}
	else {// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5; // バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; // インターバル
	}

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, // ディスプレイアダプタ
		D3DDEVTYPE_HAL, // ディスプレイタイプ
		hWnd, // フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // デバイス作成制御の組み合わせ
		&d3dpp, // デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice))) // デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダリングステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE); // Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); // αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); // テクスチャＵ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); // テクスチャＶ値の繰り返し設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // テクスチャ拡大時の補間設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // テクスチャ縮小時の補間設定

	#ifdef _DEBUG
		D3DXCreateFont(g_pD3DDevice,18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Terminal"),&g_pD3DXFont);
	#endif

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	if(g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
	}
	#ifdef _DEBUG
	if(g_pD3DXFont != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3DXFont->Release();
	}
	#endif
	// UninitInput();
	// ポリゴンの終了処理
	// UninitPlayer();
	// UninitEnemy();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// UpdateInput();
	// ポリゴンの更新処理
	// UpdatePlayer();
	// UpdateEnemy();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ポリゴンの描画処理
		// DrawEnemy();
		// DrawPlayer();

		#ifdef _DEBUG
		DrawDebugFont(); // 一番最後にDrawするように
		#endif

		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイス取得関数
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return(g_pD3DDevice);
}

#ifdef _DEBUG
// フォント表示関数
void DrawDebugFont(void) {
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	TCHAR str[256];
	wsprintf(str,_T("FPS:%d\n"),g_nCountFPS);
	g_pD3DXFont->DrawText(NULL,str,-1,&rect,DT_LEFT,D3DCOLOR_ARGB(0xff,0xff,0xff,0xff));
}
#endif
