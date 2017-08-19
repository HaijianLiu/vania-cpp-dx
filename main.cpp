
#include "Engine.h"

/*------------------------------------------------------------------------------
Engine Objects
------------------------------------------------------------------------------*/
// List of GetGameObject and Collider
std::vector<GameObject*> gameObjects;
std::vector<BoxCollider*> colliders;
// Time
Time* time = new Time();
Camera* camera = new Camera();

/*------------------------------------------------------------------------------
Scene Objects
------------------------------------------------------------------------------*/
Scene* scene = new Scene();


/*------------------------------------------------------------------------------
Debug
------------------------------------------------------------------------------*/
#ifdef _DEBUG
	LPD3DXFONT gD3DXFont = NULL; // D3D font pointer

	void DrawDebugFont() {
		RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
		char str[256];
		sprintf(str,"FPS:%d\nDelta Time:%.3f", time->countFPS, time->deltaTime);
		gD3DXFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff,0xff,0xff,0xff));
	}
#endif

/*------------------------------------------------------------------------------
Start
------------------------------------------------------------------------------*/
void Start() {
	time->Start();
	scene->Start();

	#ifdef _DEBUG
		D3DXCreateFont(GetDevice(),18,0,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Terminal"),&gD3DXFont);
	#endif

}

/*------------------------------------------------------------------------------
Delete
------------------------------------------------------------------------------*/
void Delete() {
	delete scene;
	delete camera;
	delete time;

	#ifdef _DEBUG
		if (gD3DXFont != NULL) gD3DXFont->Release();
	#endif
}

/*------------------------------------------------------------------------------
Update
------------------------------------------------------------------------------*/
void Update(void) {
	UpdateInput();
	time->Update();
	scene->Update();
}

/*------------------------------------------------------------------------------
Draw
------------------------------------------------------------------------------*/
void Draw(void) {
	ClearWindow();
	if(WindowBeginScene()) {
		scene->Draw();
		#ifdef _DEBUG
			DrawDebugFont();
		#endif
		WindowEndScene();
	}
	PresentWindow();
}



/*------------------------------------------------------------------------------
main
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (!InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow)) return -1;
	// Start
	Start();
	// Game Loop
	while(1) {
		if (CheckBreak()) break;
		// Update
		time->SetTime();
		if (time->CheckFPS(60)) {
			Update();
			Draw();
		}
	}
	// Delete
	Delete();
	return DeleteWindow();
}


/*------------------------------------------------------------------------------
Get Functions
------------------------------------------------------------------------------*/
Time* GetTime() {
	return time;
}

Camera* GetCamera() {
	return camera;
}

std::vector<BoxCollider*>* GetColliders() {
	return &colliders;
}
std::vector<GameObject*>* GetGameObjects() {
	return &gameObjects;
}
std::vector<BoxCollider*> CopyColliders() {
	return colliders;
}
std::vector<GameObject*> CopyGameObjects() {
	return gameObjects;
}
