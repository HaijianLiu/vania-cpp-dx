
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
Resources* resources = new Resources();
SceneManager* sceneManager = new SceneManager();

#ifdef _DEBUG
	Debug* debug = new Debug(sceneManager);
#endif


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Start() {
	time->Start();
	srand((unsigned)time->currentTime);
	resources->Start();
	sceneManager->Start();

	#ifdef _DEBUG
		debug->Start();
	#endif
}


/*------------------------------------------------------------------------------
< Delete >
------------------------------------------------------------------------------*/
void Delete() {
	delete resources;
	delete sceneManager;
	delete camera;
	delete time;

	#ifdef _DEBUG
		delete debug;
	#endif
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Update() {
	UpdateInput();
	time->Update();
	sceneManager->Update();
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Draw() {
	ClearWindow();
	if(WindowBeginScene()) {
		sceneManager->Draw();

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
Resources* GetResources() {
	return resources;
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
unsigned int GetCollidersSize() {
	return colliders.size();
}
unsigned int GetGameObjectsSize() {
	return gameObjects.size();
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
