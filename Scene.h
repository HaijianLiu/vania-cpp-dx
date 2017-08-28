
#ifndef _SCENE_H_
#define _SCENE_H_

class SceneManager;

class Scene {
private:

public:
	// List of GetGameObject and Collider
	std::vector<GameObject*>* gpGameObjects;
	std::vector<BoxCollider*>* gpColliders;
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;
	unsigned int startGameObjectsSize;
	unsigned int startCollidersSize;
	// SceneManager
	SceneManager* sceneManager;

	// Map Data
	Int2D mapSize = Int2D(0,0);
	int tilePixel = 16;
	Int2D tileSize = Int2D(0,0);

	// Camera
	Camera* camera;


	Scene();
	virtual ~Scene();

	virtual void Start();
	void ResetGameObjectsAndColliders();
	virtual void Update();
	void Draw();

	// Functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	bool LoadMapData(const char* path, std::vector<int>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);
};

#endif
