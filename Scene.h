
#ifndef _SCENE_H_
#define _SCENE_H_

class Scene {
private:
	// global GameObjects and Colliders parameter
	std::vector<GameObject*>* gpGameObjects;
	std::vector<BoxCollider*>* gpColliders;
	unsigned int startGameObjectsSize;
	unsigned int startCollidersSize;

public:
	// Scene GameObjects and Colliders
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;
	// SceneManager
	SceneManager* sceneManager;
	// Camera
	Camera* camera;

	// Map Data
	Int2D mapSize = Int2D(100,15);
	int tilePixel = 16;
	Int2D tileSize = Int2D(384/16,192/16);
	// Map path
	const char* cameraPath;
	const char* groundPath;
	const char* backGroundPath;
	const char* rangePath;
	// Map Object
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;
	std::vector<NoneObject*> range;

	Scene();
	virtual ~Scene();

	virtual void Start();
	void SetScene();
	virtual void Update();
	void Draw();

	// Functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	bool LoadMapData(const char* path, std::vector<Int2D>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);
	void SetPosition(GameObject* gameObject, int mapID);
};

#endif
