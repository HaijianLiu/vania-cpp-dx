
#ifndef _RESOURCES
#define _RESOURCES

class Resources {
private:
	/* data */

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
	Texture texPlayerHurt = Texture("assets/player-hurt.png",80,80);
	Texture texBullet = Texture("assets/bullet.png",4,4);
	Texture texFxDestroy = Texture("assets/fx-destroy.png",32,32);
	Texture texEnemyDestroy = Texture("assets/enemy-destroy.png",192,32);
	Texture texCrabWalk = Texture("assets/crab-walk.png",192,32);
	Texture texBlock = Texture("assets/block.png",48,16);
	Texture texUIEnergyBG = Texture("assets/ui-energy.png",112,32);
	// Animation Object
	AnimationObject* enemyDestroy;
	// Audio
	std::vector<Audio*> audShoot;
	Audio* audSceneBGM;
	Audio* audLanding;
	Audio* audPlayerHurt;
	Audio* audEnemyDamage;
	Audio* audEnemyDestroy;
	// Particle System
	ParticleSystem* fxDestroy;
	ParticleSystem* fxTail;


	Resources();
	~Resources();

	void Start();
	void LoadTexture(Texture* texture);
};

#endif
