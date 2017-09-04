
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player : public GameObject {
private:

public:
	// SceneManager
	SceneManager* sceneManager;

	// Collider
	BoxCollider* collGroundCheck;
	BoxCollider* collCeilingCheck;
	BoxCollider* collHorizonCheck;
	// Animation
	Animation* animIdle;
	Animation* animShoot;
	Animation* animRun;
	Animation* animJump;
	Animation* animDuck;
	Animation* animDuckFire;
	Animation* animHurt;
	// offset Object
	OffsetObject* leftFire;
	OffsetObject* rightFire;
	OffsetObject* leftDuckFire;
	OffsetObject* rightDuckFire;
	// Bullet
	std::vector<Bullet*> bullets;
	// UIObject
	UIObject* uiEnergyBG;
	UIObject* uiEnergy;

	// Parameter
	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;
	float fireColdDown = 0.1f;
	float hurtColdDown = 1.0f;
	float hurtFreeze = 0.3f;
	float freezeColdDown = 5.0f;
	float backSpeed = 0.5f;
	float shootEnergy = 20.0f;
	float energyRegain = 20.0f;
	float bulletDamage = 40.0f;

	// status
	bool move = false;
	bool right = true;
	bool air = true;
	bool shoot = false;
	bool duck = false;
	bool hurt = false;
	bool freeze = false;
	DWORD lastFire = 0;
	DWORD lastHurt = 0;
	DWORD lastFreeze = 0;
	float verticalSpeed = 0.0f;
	float shootAnimationLast = 0.2f;
	float deathDelay = 1.0f;
	float gameOverDelay = 3.0f;
	DWORD lastGameOver = 0;

	// Constructors
	Player ();
	~Player();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
