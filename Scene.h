
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
	Texture texTile = Texture("assets/tilesets.png",384,192);
	Texture texPlayerIdle = Texture("assets/player-idle.png",240,80);
	Texture texPlayerRun = Texture("assets/player-run-shoot.png",800,80);
	Texture texPlayerJump = Texture("assets/player-jump.png",480,80);

	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	void LoadTexture(Texture* texture);

public:
	// Camera
	Camera* camera;

	// GameObject
	Player* player;
	Ground* ground1;
	Ground* ground2;
	Ground* ground3;
	Ground* ground4;
	Ground* ground5;


	Scene();
	~Scene();

	void Start();
	void Update();
	void Draw();
};

#endif
