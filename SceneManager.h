
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

class SceneManager {
private:

public:
	// DirectX device
	LPDIRECT3DDEVICE9 device;

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
	// Audio
	std::vector<Audio*> audShoot;

	// Camera
	Camera* camera;

	// GameObject
	Player* player;
	// Particle System
	ParticleSystem* fxDestroy;
	ParticleSystem* fxTail;

	// Enemy
	Crab* crab;

	// Scene
	unsigned int activeScene;
	std::vector<Scene*> scenes;


	SceneManager();
	~SceneManager();

	void Start();
	void Update();
	void Draw();

	// Functions
	void LoadTexture(Texture* texture);
	void SetActiveScene(unsigned int i);

};

#endif
