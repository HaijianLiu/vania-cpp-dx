
#include "Engine.h"

/*------------------------------------------------------------------------------
< List of GetGameObject and Collider >
------------------------------------------------------------------------------*/
std::vector<GameObject*> gameObjects;
std::vector<BoxCollider*> colliders;

/*------------------------------------------------------------------------------
< Game Objects >
------------------------------------------------------------------------------*/
Time* time = new Time();
Camera* camera = new Camera();
Scene* scene = new Scene();

#ifdef _DEBUG
	Debug* debug = new Debug(scene);
#endif

/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Start() {
	time->Start();
	scene->Start();

	#ifdef _DEBUG
		debug->Start();
	#endif
}

/*------------------------------------------------------------------------------
< Delete >
------------------------------------------------------------------------------*/
void Delete() {
	delete scene;
	delete camera;
	delete time;

	#ifdef _DEBUG
		delete debug;
	#endif
}

/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Update(void) {
	UpdateInput();
	time->Update();
	scene->Update();
}

/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Draw(void) {
	ClearWindow();
	if(WindowBeginScene()) {
		scene->Draw();

		#ifdef _DEBUG
			debug->Draw();
		#endif

		WindowEndScene();
	}
	PresentWindow();
}

/*------------------------------------------------------------------------------
< Get Functions >
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

/*==============================================================================
< main >
==============================================================================*/
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
