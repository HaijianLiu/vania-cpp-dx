
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Boss::Boss() {
	// Camera
	this->camera = GetCamera();
	// Status
	this->status->hp = 100;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(128.0f,128.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,128,128);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,64.0f,64.0f);
	this->collider->tag = "boss";
	// GameObject
	this->core = new BossCore();
	for (unsigned int i = 0; i < 7; i++) {
		this->deathWallsRight.push_back(new DeathWall());
	}
	for (unsigned int i = 0; i < 7; i++) {
		this->deathWallsLeft.push_back(new DeathWall());
		this->deathWallsLeft.back()->right = false;
	}
	for (unsigned int i = 0; i < 4; i++) {
		this->bullets.push_back(new BossBullet());
	}
	// UIObject
	this->uiLife = new UIObject(0.0f, 0.0f, 100.0f, 2.0f);
	this->uiLife->active = false;
	this->uiBossBG = new UIObject(200.0f - 56.0f, -120.0f + 16.0f, 112.0f, 32.0f);
	this->uiBossBG->active = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Boss::~Boss() {
	// Collider
	delete this->collider;
	// GameObject
	delete this->core;
	for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) delete this->deathWallsRight[i];
	for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) delete this->deathWallsLeft[i];
	for (unsigned int i = 0; i < this->bullets.size(); i++) delete this->bullets[i];
	// UIObject
	delete this->uiLife;
	delete this->uiBossBG;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Boss::Start() {
	// Resources
	this->sprite->texture = this->resources->texBossEyeBall;
	this->uiLife->sprite->texture = this->resources->texDefault;
	this->uiBossBG->sprite->texture = this->resources->texUIBossBG;

	// GameObject
	for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) {
		this->deathWallsRight[i]->transform->position.x = this->transform->position.x + 2.24f;
		this->deathWallsRight[i]->transform->position.y = this->transform->position.y - 0.96f + 0.32f * i;
		this->deathWallsRight[i]->startPosition = this->deathWallsRight[i]->transform->position;
	}
	for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) {
		this->deathWallsLeft[i]->transform->position.x = this->transform->position.x - 2.24f;
		this->deathWallsLeft[i]->transform->position.y = this->transform->position.y - 0.96f + 0.32f * i;
		this->deathWallsLeft[i]->startPosition = this->deathWallsLeft[i]->transform->position;
	}

	// Animation MakeFrame() || Sprite MakeSlice()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Boss::Update() {
	// CheckSkill
	if (this->awake) {
		Boss::CheckSkill();
	}


	/* UIObject
	..............................................................................*/
	if (this->awake) {
		this->uiLife->active = true;
		this->uiBossBG->active = true;
		this->uiLife->offset = Float2D(200.0f - 6.0f - 0.05f * this->status->hp,  -120.0f + 20.0f);
		this->uiLife->transform->scale = Float2D(this->status->hp * 0.1f, 2.0f);
		if (!this->freeze) {
			if (this->status->hp > 600) {
				this->uiLife->sprite->SetColor(0,255,255,255);
			}
			else if (this->status->hp > 200) {
				this->uiLife->sprite->SetColor(255,192,0,255);
			}
			else {
				this->uiLife->sprite->SetColor(255,79,108,255);
			}
		}
		else {
			this->uiLife->sprite->SetColor(100,100,100,255);
		}
	}

	/* Core Transform
	..............................................................................*/
	float angle = atan((this->target->transform->position.y - this->transform->position.y) / (this->target->transform->position.x - this->transform->position.x));

	if (this->target->transform->position.x < this->transform->position.x) {
		this->core->transform->position.x = this->transform->position.x - cos(angle) * this->core->radius;
		this->core->transform->position.y = this->transform->position.y - sin(angle) * this->core->radius;
	}
	else {
		this->core->transform->position.x = this->transform->position.x + cos(angle) * this->core->radius;
		this->core->transform->position.y = this->transform->position.y + sin(angle) * this->core->radius;
	}

	/* Bullet
	..............................................................................*/
	if (this->awake) {
		if (this->time->currentTime > this->lastBullet + this->bulletColdDown * 1000.0f) {
			this->lastBullet = this->time->currentTime;
			for (unsigned int i = 0; i < this->bullets.size(); i++) {
				if (!this->bullets[i]->active) {
					this->bullets[i]->active = true;
					this->bullets[i]->status->hp = this->bullets[i]->hp;
					this->bullets[i]->transform->position.x = this->transform->position.x - 1.5f + i;
					this->bullets[i]->transform->position.y = this->transform->position.y - 1.0f;
				}
			}
		}
	}

	/* DeathWall && DeathArea
	..............................................................................*/
	if (this->awake) {
		if (this->currentSkill == DEATH_AREA_RIGHT) {
			for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) {
				this->deathWallsRight[i]->DeathArea(true);
			}
		}
		else {
			if (this->target->transform->position.x - this->transform->position.x  > this->deathWallRange) {
				for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) {
					this->deathWallsRight[i]->Forward();
				}
			}
		}
		if (this->currentSkill == DEATH_AREA_LEFT) {
			for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) {
				this->deathWallsLeft[i]->DeathArea(false);
			}
		}
		else {
			if (this->transform->position.x - this->target->transform->position.x > this->deathWallRange) {
				for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) {
					this->deathWallsLeft[i]->Forward();
				}
			}
		}
	}

	/* BGM
	..............................................................................*/
	if (this->awake) {
		if (!this->intro) {
			this->resources->audBossIntroBGM->Play();
			this->intro = true;
		}
		else {
			if (!this->resources->audBossMainBGM->Playing() && !this->resources->audBossIntroBGM->Playing()) {
				this->resources->audBossMainBGM->Play();
			}
		}
	}


	/* Death && Awake
	..............................................................................*/
	if (this->status->hp <= 0) {
		if (!this->awake) {
			if (abs(this->target->transform->position.x - this->transform->position.x) < this->deathWallRange) {
				this->awake = true;
				this->camera->SwitchTarget(this);
				this->status->hp = this->hp;
				for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) {
					this->deathWallsRight[i]->active = true;
				}
				for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) {
					this->deathWallsLeft[i]->active = true;
				}
			}
			else {
				this->status->hp = 1.0f;
			}
		}
		else {
			this->active = false;
			this->resources->audEnemyDestroy->Play();
			Instantiate(this->resources->enemyDestroy, this->transform);
			this->resources->audBossMainBGM->Stop();
			this->camera->SwitchTarget(this->target);
		}
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Boss::OnTriggerEnter(BoxCollider* other) {
	/* Damage if tag = "bullet"
	..............................................................................*/
	if (other->tag == "bullet") {
		this->sprite->Flash();
		this->status->hp -= other->gameObject->status->damage;
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Boss::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void Boss::CheckSkill() {
	if (this->time->currentTime - this->lastSkill > this->skillColdDown * 1000.0f) {
		this->currentSkill = rand() % SKILL_MAX;
		this->lastSkill = this->time->currentTime;
	}
}
