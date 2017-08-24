
#ifndef _SCENE_H_
#define _SCENE_H_

class Scene {
private:
	// DirectX device
	LPDIRECT3DDEVICE9 device;

public:
	// List of GetGameObject and Collider
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;

	// Texture
	Texture texDefault = Texture("assets/default.png",32,32);
	Texture texTile = Texture("assets/tilesets.png",384,192);
	Texture texPlayerIdle = Texture("assets/player-idle.png",240,80);
	Texture texPlayerShoot = Texture("assets/player-shoot.png",240,80);
	Texture texPlayerRun = Texture("assets/player-run-shoot.png",800,80);
	Texture texPlayerJump = Texture("assets/player-jump.png",480,80);
	Texture texPlayerDuck = Texture("assets/player-duck.png",80,80);
	Texture texPlayerDuckFire = Texture("assets/player-duck-shoot.png",240,80);
	Texture texCrabWalk = Texture("assets/crab-walk.png",192,32);
	Texture texBullet = Texture("assets/bullet.png",4,4);
	Texture texFxDestroy = Texture("assets/fx-destroy.png",32,32);

	// Map Data
	Int2D mapSize = Int2D(100,11);
	int tilePixel = 16;
	Int2D tileSize = Int2D(384/16,192/16);
	std::vector<int> groundData;
	std::vector<int> backGroundData;

	// Camera
	Camera* camera;

	// GameObject
	Player* player;
	Crab* crab;
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;
	// Particle System
	ParticleSystem* fxDestroy;
	ParticleSystem* fxTail;


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
