
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Player::Player() {
	// Status
	this->active = false;
	this->status->hp = this->hp;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(80.0f,80.0f);
	this->sprite->flashTime = this->hurtColdDown;
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animIdle = new Animation(3,1,15);
	this->animShoot = new Animation(3,1,4);
	this->animRun = new Animation(10,1,4);
	this->animJump = new Animation(6,1,4);
	this->animDuck = new Animation(1,1,60);
	this->animDuckFire = new Animation(3,1,4);
	this->animHurt = new Animation(1,1,60);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.21f,8.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collGroundCheck->tag = "ground check";
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.05f,4.0f,4.0f);
	this->collCeilingCheck->trigger = true;
	this->collCeilingCheck->tag = "ceiling check";
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.08f,24.0f,28.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "player";
	// None Object
	this->leftFire = new OffsetObject(this,-0.2f,-0.015f);
	this->rightFire = new OffsetObject(this,0.2f,-0.015f);
	this->leftDuckFire = new OffsetObject(this,-0.2f,0.1f);
	this->rightDuckFire = new OffsetObject(this,0.2f,0.1f);
	// Bullet
	for (int i = 0; i < 16; i++) {
		this->bullets.push_back(new Bullet());
		this->bullets.back()->status->damage = this->bulletDamage;
	}
	// UIObject
	this->uiEnergy = new UIObject(-200.0f + 6.5f + 49.5f, -120.0f + 19.5f,100.0f,1.0f);
	this->uiEnergyBG = new UIObject(-144.0f,-104.0f,112.0f,32.0f);
	this->score = new Score();
	// Orb
	this->orb = new Orb();
	this->orb->sprite->slice = Slice(0,48,0,16,16);
	this->orb->collider->tag = "my orb";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Player::~Player() {
	// delete objects
	delete this->animIdle;
	delete this->animShoot;
	delete this->animRun;
	delete this->animJump;
	delete this->animDuck;
	delete this->animDuckFire;
	delete this->animHurt;
	delete this->collGroundCheck;
	delete this->collCeilingCheck;
	delete this->collHorizonCheck;
	delete this->leftFire;
	delete this->rightFire;
	delete this->leftDuckFire;
	delete this->rightDuckFire;
	for (unsigned int i = 0; i < this->bullets.size(); i++) {
		delete this->bullets[i];
	}
	// UIObject
	delete this->uiEnergy;
	delete this->uiEnergyBG;
	delete this->score;
	// Orb
	delete this->orb;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	// Resources
	this->animIdle->sprite->device = this->resources->device;
	this->animIdle->sprite->texture = this->resources->texPlayerIdle;
	this->animShoot->sprite->device = this->resources->device;
	this->animShoot->sprite->texture = this->resources->texPlayerShoot;
	this->animRun->sprite->device = this->resources->device;
	this->animRun->sprite->texture = this->resources->texPlayerRun;
	this->animJump->sprite->device = this->resources->device;
	this->animJump->sprite->texture = this->resources->texPlayerJump;
	this->animDuck->sprite->device = this->resources->device;
	this->animDuck->sprite->texture = this->resources->texPlayerDuck;
	this->animDuckFire->sprite->device = this->resources->device;
	this->animDuckFire->sprite->texture = this->resources->texPlayerDuckFire;
	this->animHurt->sprite->device = this->resources->device;
	this->animHurt->sprite->texture = this->resources->texPlayerHurt;
	this->uiEnergy->sprite->texture = this->resources->texDefault;
	this->uiEnergyBG->sprite->texture = this->resources->texUIEnergyBG;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animIdle->MakeFrame();
	this->animShoot->MakeFrame();
	this->animRun->MakeFrame();
	this->animJump->MakeFrame();
	this->animDuck->MakeFrame();
	this->animDuckFire->MakeFrame();
	this->animHurt->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {
	/* HP
	..............................................................................*/
	if (!this->freeze) {
		this->status->hp += this->energyRegain * this->time->deltaTime;
	}
	else {
		if (this->time->currentTime > this->lastFreeze + this->freezeColdDown * 1000.0f) {
			this->freeze = false;
		}
	}
	if (this->status->hp < 0) this->status->hp = 0;
	if (this->status->hp > this->hp) this->status->hp = this->hp;

	/* UIObject
	..............................................................................*/
	this->uiEnergy->offset = Float2D(-200.0f + 6.0f + 0.5f * this->status->hp,  -120.0f + 20.0f);
	this->uiEnergy->transform->scale = Float2D(this->status->hp * 1.0f, 2.0f);
	if (!this->freeze) {
		if (this->status->hp > 0.6f * this->hp) {
			this->uiEnergy->sprite->SetColor(0,255,255,255);
		}
		else if (this->status->hp > 0.2f * this->hp) {
			this->uiEnergy->sprite->SetColor(255,192,0,255);
		}
		else {
			this->uiEnergy->sprite->SetColor(255,79,108,255);
		}
	}
	else {
		this->uiEnergy->sprite->SetColor(100,100,100,255);
	}

	/* Transform
	..............................................................................*/
	if (!this->hurt) {
		// move
		if (GetKeyboardPress(DIK_LEFT)) {
			this->move = true;
			this->right = false;
			this->transform->position.x -= this->speed * this->time->deltaTime;
		}
		else if (GetKeyboardPress(DIK_RIGHT)) {
			this->move = true;
			this->right = true;
			this->transform->position.x += this->speed * this->time->deltaTime;
		}
		else {
			this->move = false;
		}
		// jump
		if (GetKeyboardTrigger(DIK_SPACE)) {
			if (!this->air) {
				this->verticalSpeed = this->jumpPower;
				this->air = true;
			}
		}
		// duck
		if (GetKeyboardPress(DIK_DOWN)) {
			if (!this->air) {
				this->duck = true;
			}
		}
		else {
			this->duck = false;
		}
	}
	else {
		if (this->right) {
			this->transform->position.x -= this->backSpeed * this->time->deltaTime;
		}
		else {
			this->transform->position.x += this->backSpeed * this->time->deltaTime;
		}
	}

	/* Death
	..............................................................................*/
	if (this->status->hp <= 0 && !this->hurt && this->draw) {
		this->draw = false;
		this->resources->audPlayerDestroy->Play();
		Instantiate(this->resources->playerDestroy, this->transform);
	}

	/* GameOver
	..............................................................................*/
	if (this->status->hp <= 0 && this->time->currentTime > this->lastHurt + this->gameOverDelay * 1000.0f) {
		this->active = false;
		this->uiEnergy->active = false;
		this->uiEnergyBG->active = false;
		this->sceneManager->SetActiveScene(this->sceneManager->gameOverScene);
		this->lastGameOver = this->time->currentTime;
		// Score
		for (unsigned int i = 0; i < this->score->numbers.size(); i++) {
			this->score->numbers[i]->active = false;
			this->score->numbers[i]->sprite->slice = Slice(0,0,0,this->score->size.x,this->score->size.y);
		}
		this->score->numbers[0]->active = true;

		this->orb->status->hp = this->score->score;
		this->score->score = 0;
		this->score->willAdd = 0;
		Instantiate(this->orb, this->transform);
	}

	/* Gravity
	..............................................................................*/
	this->verticalSpeed -= this->gravity * this->time->deltaTime;
	if (this->verticalSpeed <= - 0.8f * this->jumpPower) {
		this->verticalSpeed = - 0.8f * this->jumpPower;
	}
	this->transform->position.y -= this->verticalSpeed * this->time->deltaTime;
	if (this->verticalSpeed < -1.0f) {
		this->air = true;
	}


	/* Animation
	// Animation SetTexture() || Sprite SetTexture()
	..............................................................................*/

	// Shoot Flag
	if (this->time->currentTime > this->lastFire + this->shootAnimationLast * 1000.0f) {
		this->shoot = false;
	}

	// Hurt Flag
	if (this->status->hp > 0) {
		if (this->time->currentTime > this->lastHurt + this->hurtFreeze * 1000.0f) {
			this->hurt = false;
		}
	}
	else {
		if (this->time->currentTime > this->lastHurt + this->deathDelay * 1000.0f) {
			this->hurt = false;
		}
	}

	/* Animation
	..............................................................................*/
	if (!this->hurt) {
		if (this->air) {
			this->animJump->sprite->flipX = !this->right;
			this->animJump->SetTexture(this->sprite->vertex);
			this->sprite->texture = this->animJump->sprite->texture;
		}
		else {
			if (this->move) {
				this->animRun->sprite->flipX = !this->right;
				this->animRun->SetTexture(this->sprite->vertex);
				this->sprite->texture = this->animRun->sprite->texture;
			}
			if (!this->move) {
				if (this->duck) {
					if (this->shoot) {
						this->animDuckFire->sprite->flipX = !this->right;
						this->animDuckFire->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animDuckFire->sprite->texture;
					}
					else {
						this->animDuck->sprite->flipX = !this->right;
						this->animDuck->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animDuck->sprite->texture;
					}
				}
				else {
					if (this->shoot) {
						this->animShoot->sprite->flipX = !this->right;
						this->animShoot->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animShoot->sprite->texture;
					}
					else{
						this->animIdle->sprite->flipX = !this->right;
						this->animIdle->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animIdle->sprite->texture;
					}
				}
			}
		}
	}
	else {
		this->animHurt->sprite->flipX = !this->right;
		this->animHurt->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animHurt->sprite->texture;
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Player::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground" || other->tag == "death wall") {
		if (this->collGroundCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
			this->air = false;
			if (this->verticalSpeed <= -0.2f * this->jumpPower) {
				this->resources->audLanding->Play();
			}
			this->verticalSpeed = 0.0f;
		}
		if (this->collHorizonCheck->enter == true) {
			if (this->transform->position.x > other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x + other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x + this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
			}
			if (this->transform->position.x < other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x - other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x - this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
			}
		}
		if (this->collCeilingCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y + other->halfSize.y * PIXEL_TO_UNIT - this->collCeilingCheck->offset.y + this->collCeilingCheck->halfSize.y * PIXEL_TO_UNIT;
			this->verticalSpeed = 0.0f;
		}
	}
	/* Shield if tag = "enemy"
	..............................................................................*/
	if (other->tag == "enemy" || other->tag == "death wall" || other->tag == "ball enemy") {
		if (this->status->hp > 0 && this->time->currentTime > this->lastHurt + this->hurtColdDown * 1000.0f) {
			this->hurt = true;
			this->lastHurt = this->time->currentTime;
			this->freeze = true;
			this->lastFreeze = this->time->currentTime;
			this->status->hp -= other->gameObject->status->damage;
			if (this->status->hp <= 0) {
				this->resources->audPlayerDeath->Play();
			}
			else {
				this->resources->audPlayerHurt->Play();
			}
			if (other->gameObject->transform->position.x > this->transform->position.x) {
				this->right = true;
			}
			else {
				this->right = false;
			}
			this->verticalSpeed = 0.5f * this->jumpPower;
			this->sprite->Flash();
		}
	}

	/* add score if tag = "orb"
	..............................................................................*/
	if (other->tag == "orb") {
		this->score->WillAdd((unsigned int)other->gameObject->status->hp);
	}
	if (other->tag == "my orb") {
		this->score->WillAdd((unsigned int)other->gameObject->status->hp);
		this->resources->audOrbReturn->Play();
	}
	/*  if tag = "item"
	..............................................................................*/
	if (other->tag == "item") {
		if (other->gameObject->status->tag == "dark") {
			this->energyRegain += 5.0f;
			this->hurtColdDown += 0.5f;
			this->sprite->flashTime = this->hurtColdDown;
		}
		if (other->gameObject->status->tag == "gold") {
			this->energyRegain += 10.0f;
		}
		if (other->gameObject->status->tag == "sliver") {
			this->fireColdDown = 0.05f;
		}
		if (other->gameObject->status->tag == "bronze") {
			this->hurtColdDown += 1.0f;
			this->sprite->flashTime = this->hurtColdDown;
		}
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Player::FixedUpdate() {
	/* Fire
	..............................................................................*/
	if (!this->hurt) {
		if (GetKeyboardTrigger(DIK_F)) {
			if (this->time->currentTime > this->lastFire + this->fireColdDown * 1000.0f) {
				if (this->status->hp > this->shootEnergy) {
					this->shoot = true;
					this->status->hp -= this->shootEnergy;
					for (unsigned int i = 0; i < this->resources->audShoot.size(); i++) {
						if (!this->resources->audShoot[i]->Playing()) {
							this->resources->audShoot[i]->Play();
							break;
						}
					}
					for (unsigned int i = 0; i < this->bullets.size(); i++) {
						if (!this->bullets[i]->active) {
							this->lastFire = this->time->currentTime;
							this->bullets[i]->birthTime = this->time->currentTime;
							this->bullets[i]->right = this->right;
							this->bullets[i]->active = true;
							if (this->right) {
								if (this->duck && !this->move && !this->air) {
									this->bullets[i]->transform->position = this->rightDuckFire->transform->position;
								}
								else {
									this->bullets[i]->transform->position = this->rightFire->transform->position;
								}
							}
							else {
								if (this->duck && !this->move && !this->air) {
									this->bullets[i]->transform->position = this->leftDuckFire->transform->position;
								}
								else {
									this->bullets[i]->transform->position = this->leftFire->transform->position;
								}
							}
							break;
						}
					}
				}
				else {
					this->resources->audPlayerNoAmmo->Play();
				}
			}
		}
	}
}
