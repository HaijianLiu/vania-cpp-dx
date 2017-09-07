
#include "Engine.h"


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Resources::Resources() {
	// Animation Object
	this->enemyDestroy = new AnimationObject(32,32,6,1,4);
	this->playerDestroy = new AnimationObject(67,48,5,1,4);
	// Audio
	for (unsigned int i = 0; i < 4; i++) {
		this->audShoot.push_back(new Audio("assets/Sound/SE/sfx_wpn_laser8.wav"));
	}
	this->audSceneBGM = new Audio("assets/Sound/BGM/Venus.wav");
	this->audSceneBGM->loop = true;
	this->audBossIntroBGM = new Audio("assets/Sound/BGM/BossIntro.wav");
	this->audBossMainBGM = new Audio("assets/Sound/BGM/BossMain.wav");
	this->audBossMainBGM->loop = true;
	this->audLanding = new Audio("assets/Sound/SE/sfx_movement_jump14_landing.wav");
	this->audPlayerHurt = new Audio("assets/Sound/SE/sfx_sounds_error14.wav");
	this->audPlayerDeath = new Audio("assets/Sound/SE/sfx_deathscream_human1.wav");
	this->audPlayerDestroy = new Audio("assets/Sound/SE/sfx_exp_medium1.wav");
	this->audPlayerNoAmmo = new Audio("assets/Sound/SE/sfx_wpn_noammo1.wav");
	this->audEnemyDamage = new Audio("assets/Sound/SE/sfx_sounds_impact1.wav");
	this->audEnemyDestroy = new Audio("assets/Sound/SE/sfx_exp_shortest_soft9.wav");
	this->audBallBounce = new Audio("assets/Sound/SE/sfx_sounds_Blip4.wav");
	this->audOrbGet = new Audio("assets/Sound/SE/sfx_sounds_powerup10.wav");
	this->audOrbReturn = new Audio("assets/Sound/SE/sfx_sounds_powerup1.wav");
	this->audCheckPoint = new Audio("assets/Sound/SE/sfx_sounds_powerup18.wav");
	this->audCurser = new Audio("assets/Sound/SE/sfx_sounds_Blip7.wav");
	this->audStart = new Audio("assets/Sound/SE/Intro_Jingle.wav");
	// ParticleSystem
	this->fxTail = new ParticleSystem(100);
	this->fxTail->rateOverTime = false;
	this->fxTail->SetStartLifeTimeRange(1.0f,2.0f);
	this->fxTail->SetStartSpeedRange(0.02f,0.2f);
	this->fxTail->SetStartSizeRange(0.01f,0.02f);
	this->fxTail->SetStartAngleRange(0.0f,2.0f*PI);
	this->fxTail->SetGravity(0.0f);
	this->fxTail->SetColor(63,140,242,255);
	this->fxDestroy = new ParticleSystem(40);
	this->fxDestroy->SetStartLifeTimeRange(0.1f,0.4f);
	this->fxDestroy->SetStartSpeedRange(0.2f,1.0f);
	this->fxDestroy->SetStartSizeRange(0.05f,0.1f);
	this->fxDestroy->SetGravity(0.0f);
	this->fxOrb = new ParticleSystem(50);
	this->fxOrb->rate = 1;
	this->fxOrb->SetStartLifeTimeRange(0.5f,1.0f);
	this->fxOrb->SetStartSpeedRange(0.01f,0.2f);
	this->fxOrb->SetStartSizeRange(0.02f,0.04f);
	this->fxOrb->SetStartAngleRange(0.0f,2.0f*PI);
	this->fxOrb->SetGravity(-0.05f);
	this->fxOrb->SetColor(255,255,255,255);
	this->fxItem = new ParticleSystem(50);
	// this->fxItem->rate = 1;
	this->fxItem->SetStartLifeTimeRange(0.5f,2.0f);
	this->fxItem->SetStartSpeedRange(0.01f,0.2f);
	this->fxItem->SetStartSizeRange(0.02f,0.04f);
	this->fxItem->SetStartAngleRange(0.0f,2.0f*PI);
	this->fxItem->SetGravity(-0.07f);
	this->fxItem->SetColor(255,255,255,255);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Resources::~Resources() {
	// Texture
	if (this->texDefault.texture != NULL) this->texDefault.texture->Release();
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texCheckPoint.texture != NULL) this->texCheckPoint.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerShoot.texture != NULL) this->texPlayerShoot.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();
	if (this->texPlayerDuck.texture != NULL) this->texPlayerDuck.texture->Release();
	if (this->texPlayerDuckFire.texture != NULL) this->texPlayerDuckFire.texture->Release();
	if (this->texPlayerHurt.texture != NULL) this->texPlayerHurt.texture->Release();
	if (this->texPlayerDestroy.texture != NULL) this->texPlayerDestroy.texture->Release();
	if (this->texBullet.texture != NULL) this->texBullet.texture->Release();
	if (this->texFxDestroy.texture != NULL) this->texFxDestroy.texture->Release();
	if (this->texEnemyDestroy.texture != NULL) this->texEnemyDestroy.texture->Release();
	if (this->texCrabWalk.texture != NULL) this->texCrabWalk.texture->Release();
	if (this->texFlyer.texture != NULL) this->texFlyer.texture->Release();
	if (this->texJumperIdle.texture != NULL) this->texJumperIdle.texture->Release();
	if (this->texJumperJump.texture != NULL) this->texJumperJump.texture->Release();
	if (this->texBall.texture != NULL) this->texBall.texture->Release();
	if (this->texGhost.texture != NULL) this->texGhost.texture->Release();
	if (this->texBossEyeBall.texture != NULL) this->texBossEyeBall.texture->Release();
	if (this->texBossCore.texture != NULL) this->texBossCore.texture->Release();
	if (this->texDeathWall.texture != NULL) this->texDeathWall.texture->Release();
	if (this->texBossBullet.texture != NULL) this->texBossBullet.texture->Release();
	if (this->texBossBiteAppear.texture != NULL) this->texBossBiteAppear.texture->Release();
	if (this->texBossBiteDisappear.texture != NULL) this->texBossBiteDisappear.texture->Release();
	if (this->texBossBiteBite.texture != NULL) this->texBossBiteBite.texture->Release();
	if (this->texBlock.texture != NULL) this->texBlock.texture->Release();
	if (this->texOrb.texture != NULL) this->texOrb.texture->Release();
	if (this->texItem.texture != NULL) this->texItem.texture->Release();
	if (this->texItemLight.texture != NULL) this->texItemLight.texture->Release();
	if (this->texUIEnergyBG.texture != NULL) this->texUIEnergyBG.texture->Release();
	if (this->texUIBossBG.texture != NULL) this->texUIBossBG.texture->Release();
	if (this->texUIGameOverText.texture != NULL) this->texUIGameOverText.texture->Release();
	if (this->texUITitle.texture != NULL) this->texUITitle.texture->Release();
	if (this->texUITitleText.texture != NULL) this->texUITitleText.texture->Release();
	if (this->texUINumbers.texture != NULL) this->texUINumbers.texture->Release();
	if (this->texUIItemGold.texture != NULL) this->texUIItemGold.texture->Release();
	if (this->texUIItemSliver.texture != NULL) this->texUIItemSliver.texture->Release();
	if (this->texUIItemBronze.texture != NULL) this->texUIItemBronze.texture->Release();
	if (this->texUIItemDark.texture != NULL) this->texUIItemDark.texture->Release();
	if (this->texBackGround2nd.texture != NULL) this->texBackGround2nd.texture->Release();
	if (this->texBackGround4th.texture != NULL) this->texBackGround4th.texture->Release();
	if (this->texBackGround2ndTissue.texture != NULL) this->texBackGround2ndTissue.texture->Release();
	if (this->texBackGround2ndShip.texture != NULL) this->texBackGround2ndShip.texture->Release();

	// AnimationObject
	delete this->enemyDestroy;
	delete this->playerDestroy;
	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		delete this->audShoot[i];
	}
	delete this->audSceneBGM;
	delete this->audBossIntroBGM;
	delete this->audBossMainBGM;
	delete this->audLanding;
	delete this->audPlayerHurt;
	delete this->audPlayerDeath;
	delete this->audPlayerDestroy;
	delete this->audPlayerNoAmmo;
	delete this->audEnemyDamage;
	delete this->audEnemyDestroy;
	delete this->audBallBounce;
	delete this->audOrbGet;
	delete this->audOrbReturn;
	delete this->audCheckPoint;
	delete this->audCurser;
	delete this->audStart;
	// ParticleSystem
	delete this->fxDestroy;
	delete this->fxTail;
	delete this->fxOrb;
	delete this->fxItem;
}


/*------------------------------------------------------------------------------
< Start > before SceneManager Start && before GameObject PreStart
------------------------------------------------------------------------------*/
void Resources::Start() {
	// GetDevice
	this->device = GetDevice();

	// LoadTexture
	Resources::LoadTexture(&this->texDefault);
	Resources::LoadTexture(&this->texTile);
	Resources::LoadTexture(&this->texCheckPoint);
	Resources::LoadTexture(&this->texPlayerIdle);
	Resources::LoadTexture(&this->texPlayerShoot);
	Resources::LoadTexture(&this->texPlayerRun);
	Resources::LoadTexture(&this->texPlayerJump);
	Resources::LoadTexture(&this->texPlayerDuck);
	Resources::LoadTexture(&this->texPlayerDuckFire);
	Resources::LoadTexture(&this->texPlayerHurt);
	Resources::LoadTexture(&this->texPlayerDestroy);
	Resources::LoadTexture(&this->texBullet);
	Resources::LoadTexture(&this->texFxDestroy);
	Resources::LoadTexture(&this->texEnemyDestroy);
	Resources::LoadTexture(&this->texCrabWalk);
	Resources::LoadTexture(&this->texFlyer);
	Resources::LoadTexture(&this->texJumperIdle);
	Resources::LoadTexture(&this->texJumperJump);
	Resources::LoadTexture(&this->texBall);
	Resources::LoadTexture(&this->texGhost);
	Resources::LoadTexture(&this->texBossEyeBall);
	Resources::LoadTexture(&this->texBossCore);
	Resources::LoadTexture(&this->texDeathWall);
	Resources::LoadTexture(&this->texBossBullet);
	Resources::LoadTexture(&this->texBossBiteAppear);
	Resources::LoadTexture(&this->texBossBiteDisappear);
	Resources::LoadTexture(&this->texBossBiteBite);
	Resources::LoadTexture(&this->texBlock);
	Resources::LoadTexture(&this->texOrb);
	Resources::LoadTexture(&this->texItem);
	Resources::LoadTexture(&this->texItemLight);
	Resources::LoadTexture(&this->texUIEnergyBG);
	Resources::LoadTexture(&this->texUIBossBG);
	Resources::LoadTexture(&this->texUIGameOverText);
	Resources::LoadTexture(&this->texUITitle);
	Resources::LoadTexture(&this->texUITitleText);
	Resources::LoadTexture(&this->texUINumbers);
	Resources::LoadTexture(&this->texUIItemGold);
	Resources::LoadTexture(&this->texUIItemSliver);
	Resources::LoadTexture(&this->texUIItemBronze);
	Resources::LoadTexture(&this->texUIItemDark);
	Resources::LoadTexture(&this->texBackGround2nd);
	Resources::LoadTexture(&this->texBackGround4th);
	Resources::LoadTexture(&this->texBackGround2ndTissue);
	Resources::LoadTexture(&this->texBackGround2ndShip);

	// AnimationObject
	this->enemyDestroy->animation->sprite->device = this->device;
	this->enemyDestroy->animation->sprite->texture = this->texEnemyDestroy;
	this->playerDestroy->animation->sprite->device = this->device;
	this->playerDestroy->animation->sprite->texture = this->texPlayerDestroy;
	// Audio
	for (unsigned int i = 0; i < this->audShoot.size(); i++) {
		this->audShoot[i]->LoadAudio();
	}
	this->audSceneBGM->LoadAudio();
	this->audBossIntroBGM->LoadAudio();
	this->audBossMainBGM->LoadAudio();
	this->audLanding->LoadAudio();
	this->audPlayerHurt->LoadAudio();
	this->audPlayerDeath->LoadAudio();
	this->audPlayerDestroy->LoadAudio();
	this->audPlayerNoAmmo->LoadAudio();
	this->audEnemyDamage->LoadAudio();
	this->audEnemyDestroy->LoadAudio();
	this->audBallBounce->LoadAudio();
	this->audOrbGet->LoadAudio();
	this->audOrbReturn->LoadAudio();
	this->audCheckPoint->LoadAudio();
	this->audCurser->LoadAudio();
	this->audStart->LoadAudio();
	// ParticleSystem
	this->fxDestroy->LinkTexture(this->texFxDestroy);
	this->fxTail->LinkTexture(this->texDefault);
	this->fxOrb->LinkTexture(this->texDefault);
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void Resources::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
}
