
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
	Texture texTile = Texture("assets/tilesets.png",384,320);
	Texture texCheckPoint = Texture("assets/check-point.png",64,32);
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
	Texture texFlyer = Texture("assets/flyer.png",64,32);
	Texture texJumperIdle = Texture("assets/jumper-idle.png",188,32);
	Texture texJumperJump = Texture("assets/jumper-jump.png",47,32);
	Texture texBall = Texture("assets/ball.png",16,16);
	Texture texBossEyeBall = Texture("assets/boss-eye-ball.png",128,128);
	Texture texBossCore = Texture("assets/boss-eye-core.png",32,32);
	Texture texDeathWall = Texture("assets/death-wall.png",32,32);
	Texture texBossBullet = Texture("assets/boss-bullet.png",147,21);
	Texture texBossBiteAppear = Texture("assets/death-bite-appear.png",256,64);
	Texture texBossBiteDisappear = Texture("assets/death-bite-disappear.png",256,64);
	Texture texBossBiteBite = Texture("assets/death-bite-bite.png",384,64);
	Texture texBlock = Texture("assets/block.png",48,16);
	Texture texOrb = Texture("assets/score.png",48,16);
	Texture texUIEnergyBG = Texture("assets/ui-energy.png",112,32);
	Texture texUIBossBG = Texture("assets/ui-boss.png",112,32);
	// Animation Object
	AnimationObject* enemyDestroy;
	// Audio
	std::vector<Audio*> audShoot;
	Audio* audSceneBGM;
	Audio* audBossIntroBGM;
	Audio* audBossMainBGM;
	Audio* audLanding;
	Audio* audPlayerHurt;
	Audio* audPlayerNoAmmo;
	Audio* audEnemyDamage;
	Audio* audEnemyDestroy;
	Audio* audBallBounce;
	Audio* audOrbGet;
	// Particle System
	ParticleSystem* fxDestroy;
	ParticleSystem* fxTail;
	ParticleSystem* fxOrb;


	Resources();
	~Resources();

	void Start();
	void LoadTexture(Texture* texture);
};

#endif
