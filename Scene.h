
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

	SceneManager* sceneManager;

	// Map Data
	Int2D mapSize = Int2D(100,11);
	int tilePixel = 16;
	Int2D tileSize = Int2D(384/16,192/16);
	std::vector<int> cameraData;
	std::vector<int> groundData;
	std::vector<int> backGroundData;

	// Camera
	Camera* camera;
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;


	Scene();
	~Scene();

	void Start();
	void Update();
	void Draw();

	// Functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	void LoadTexture(Texture* texture);
	bool LoadMapData(const char* path, std::vector<int>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);
};

#endif
