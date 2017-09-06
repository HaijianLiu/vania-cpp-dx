
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Boss::Boss() {
	// Camera
	this->camera = GetCamera();
	// Status
	this->status->hp = this->sleepHP;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(128.0f,128.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,128,128);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,64.0f,64.0f);
	this->collider->tag = "boss";
	// OffsetObject
	this->leftTarget = new OffsetObject(this,-2.0f,0.01f);
	this->rightTarget = new OffsetObject(this,2.0f,0.01f);
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
	this->deathBite = new DeathBite();
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
	// OffsetObject
	delete this->leftTarget;
	delete this->rightTarget;
	// GameObject
	delete this->core;
	for (unsigned int i = 0; i < this->deathWallsRight.size(); i++) delete this->deathWallsRight[i];
	for (unsigned int i = 0; i < this->deathWallsLeft.size(); i++) delete this->deathWallsLeft[i];
	for (unsigned int i = 0; i < this->bullets.size(); i++) delete this->bullets[i];
	delete this->deathBite;
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

	// target
	this->core->parent = this;
	this->core->target = this->target;
	this->deathBite->target = this->target;

	// DeathWall
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

	/* Core Transform
	..............................................................................*/
	if (this->currentSkill == DEATH_AREA_LEFT) {
		this->core->sprite->SetColor(255,0,0,255);
		this->core->target = this->leftTarget;
	}
	if (this->currentSkill == DEATH_AREA_RIGHT) {
		this->core->sprite->SetColor(255,0,0,255);
		this->core->target = this->rightTarget;
	}
	if (this->currentSkill == DEATH_BITE) {
		this->core->sprite->SetColor(189,29,255,255);
	}
	if (this->currentSkill == NONE_SKILL) {
		this->core->sprite->SetColor(255,255,255,255);
		this->core->target = this->target;
	}
	this->core->FollowTarget();

	/* awake
	..............................................................................*/
	if (this->awake) {
		/* Phase
		..............................................................................*/
		if (this->status->hp > 0.8f * this->hp) {
			this->phase = 0;
		}
		else if (this->status->hp > 0.5f * this->hp) {
			this->phase = 1;
		}
		else {
			this->phase = 2;
		}

		/* CheckSkill
		..............................................................................*/
		if (this->phase > 0) {
			Boss::CheckSkill();
		}

		/* UIObject
		..............................................................................*/
		this->uiLife->active = true;
		this->uiBossBG->active = true;
		this->uiLife->offset = Float2D(200.0f - 6.0f - 50.0f * this->status->hp / this->hp,  -120.0f + 20.0f);
		this->uiLife->transform->scale = Float2D(this->status->hp / this->hp * 100.0f, 2.0f);
		this->uiLife->sprite->SetColor(255,79,108,255);

		this->transform->position.y += 0.003f * sin(this->time->currentTime/400.0f);

		/* Bullet
		..............................................................................*/
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

		/* DeathWall && DeathArea
		..............................................................................*/
		if (this->currentSkill == DEATH_AREA_RIGHT && this->time->currentTime > this->lastSkill + this->skillDelay * 1000.0f) {
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
		if (this->currentSkill == DEATH_AREA_LEFT && this->time->currentTime > this->lastSkill + this->skillDelay * 1000.0f) {
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

		/* DeatBite
		..............................................................................*/
		if (this->currentSkill == DEATH_BITE && this->time->currentTime > this->lastSkill + this->skillDelay * 1000.0f) {
			this->deathBite->Appear();
		}

		/* BGM
		..............................................................................*/
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
	// Get Skill every skillColdDown
	if (this->time->currentTime > this->lastSkill + this->skillColdDown * 1000.0f) {
		this->currentSkill = rand() % this->phase;
		this->lastSkill = this->time->currentTime;

		if (this->currentSkill == DEATH_BITE) {
			if (this->deathBite->active) {
				if (this->phase == 1) {
					this->currentSkill = NONE_SKILL;
				}
				else {
					this->currentSkill = DEATH_AREA;
				}
			}
		}

		if (this->currentSkill == DEATH_AREA) {
			if (rand() % 2 == 0) {
				this->currentSkill = DEATH_AREA_LEFT;
			}
			else {
				this->currentSkill = DEATH_AREA_RIGHT;
			}
		}
	}

	// Check Reset to NONE_SKILL every Update
	if (this->currentSkill == DEATH_BITE) {
		if (this->time->currentTime > this->lastSkill + this->deathBiteTime * 1000.0f) {
			this->currentSkill = NONE_SKILL;
		}
	}

	if (this->currentSkill == DEATH_AREA_LEFT || this->currentSkill == DEATH_AREA_RIGHT) {
		if (this->time->currentTime > this->lastSkill + this->deathAreaTime * 1000.0f) {
			this->currentSkill = NONE_SKILL;
		}
	}

}
