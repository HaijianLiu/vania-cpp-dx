
/*------------------------------------------------------------------------------
Macross
------------------------------------------------------------------------------*/
#define CLASS_NAME _T("AppClass")
#define WINDOW_NAME _T("Vania")


/*------------------------------------------------------------------------------
Functions
------------------------------------------------------------------------------*/
bool InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDirectX(HWND hWnd, BOOL bWindow);
HRESULT InitSound(HWND hWnd);
bool CheckBreak();
void ClearWindow();
bool WindowBeginScene();
void WindowEndScene();
void PresentWindow();
int DeleteWindow();
