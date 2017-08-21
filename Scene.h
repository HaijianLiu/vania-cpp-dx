
#ifndef _SCENE_H_
#define _SCENE_H_

class Scene {
private:
	// DirectX device
	LPDIRECT3DDEVICE9 device;
	// List of GetGameObject and Collider
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;

	// Texture
	Texture texTile = Texture("assets/tilesets.png",624,160);
	Texture texPlayerIdle = Texture("assets/player-idle.png",240,80);
	Texture texPlayerRun = Texture("assets/player-run-shoot.png",800,80);
	Texture texPlayerJump = Texture("assets/player-jump.png",480,80);

	// Map Data
	Int2D mapSize = Int2D(20,20);
	int tilePixel = 16;
	Int2D tileSize = Int2D(624/16,160/16);
	std::vector<int> groundData;

	// private functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	void LoadTexture(Texture* texture);
	bool LoadMapData(const char* path, std::vector<int>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);

public:
	// Camera
	Camera* camera;

	// GameObject
	Player* player;
	std::vector<Ground*> grounds;


	Scene();
	~Scene();

	void Start();
	void Update();
	void Draw();
};

#endif
