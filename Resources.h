
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
	Texture texPlayerDestroy = Texture("assets/player-destroy.png",335,48);
	Texture texBullet = Texture("assets/bullet.png",4,4);
	Texture texFxDestroy = Texture("assets/fx-destroy.png",32,32);
	Texture texEnemyDestroy = Texture("assets/enemy-destroy.png",192,32);
	Texture texCrabWalk = Texture("assets/crab-walk.png",192,32);
	Texture texFlyer = Texture("assets/flyer.png",64,32);
	Texture texJumperIdle = Texture("assets/jumper-idle.png",188,32);
	Texture texJumperJump = Texture("assets/jumper-jump.png",47,32);
	Texture texBall = Texture("assets/ball.png",16,16);
	Texture texGhost = Texture("assets/ghost.png",112,37);
	Texture texBossEyeBall = Texture("assets/boss-eye-ball.png",128,128);
	Texture texBossCore = Texture("assets/boss-eye-core.png",32,32);
	Texture texDeathWall = Texture("assets/death-wall.png",32,32);
	Texture texBossBullet = Texture("assets/boss-bullet.png",147,21);
	Texture texBossBiteAppear = Texture("assets/death-bite-appear.png",256,64);
	Texture texBossBiteDisappear = Texture("assets/death-bite-disappear.png",256,64);
	Texture texBossBiteBite = Texture("assets/death-bite-bite.png",384,64);
	Texture texBlock = Texture("assets/block.png",48,16);
	Texture texOrb = Texture("assets/score.png",64,16);
	Texture texItem = Texture("assets/item.png",64,16);
	Texture texItemLight = Texture("assets/item-light.png",64,64);
	Texture texUIEnergyBG = Texture("assets/ui-energy.png",112,32);
	Texture texUIBossBG = Texture("assets/ui-boss.png",112,32);
	Texture texUIGameOverText = Texture("assets/ui-toribodose.png",64,16);
	Texture texUITitle = Texture("assets/title.png",400,250);
	Texture texUITitleText = Texture("assets/title-text.png",64,24);
	Texture texUINumbers = Texture("assets/ui-numbers.png",90,7);
	Texture texUIItemGold = Texture("assets/item-info-gold.png",256,128);
	Texture texUIItemSliver = Texture("assets/item-info-sliver.png",256,128);
	Texture texUIItemBronze = Texture("assets/item-info-bronze.png",256,128);
	Texture texUIItemDark = Texture("assets/item-info-dark.png",256,128);
	Texture texBackGround2nd = Texture("assets/background-2nd.png",272,176);
	Texture texBackGround4th = Texture("assets/background-4th.png",240,176);
	Texture texBackGround2ndTissue = Texture("assets/background-2th-tissue.png",144,144);
	Texture texBackGround2ndShip = Texture("assets/background-2nd-ship.png",64,64);

	// Animation Object
	AnimationObject* enemyDestroy;
	AnimationObject* playerDestroy;
	// Audio
	std::vector<Audio*> audShoot;
	Audio* audSceneBGMBasic;
	Audio* audSceneBGMMap;
	Audio* audSceneBGMMars;
	Audio* audBossIntroBGM;
	Audio* audBossMainBGM;
	Audio* audBossDead;
	Audio* audClear;
	Audio* audLanding;
	Audio* audPlayerHurt;
	Audio* audPlayerDeath;
	Audio* audPlayerDestroy;
	Audio* audPlayerNoAmmo;
	Audio* audEnemyDamage;
	Audio* audEnemyDestroy;
	Audio* audBallBounce;
	Audio* audOrbGet;
	Audio* audOrbReturn;
	Audio* audCheckPoint;
	Audio* audCurser;
	Audio* audStart;
	// Particle System
	ParticleSystem* fxDestroy;
	ParticleSystem* fxTail;
	ParticleSystem* fxOrb;
	ParticleSystem* fxItem;


	Resources();
	~Resources();

	void Start();
	void LoadTexture(Texture* texture);
};

#endif
