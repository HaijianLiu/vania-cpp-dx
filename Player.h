
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// GameObject
	GameObject* gameObject;
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
	// offset Object
	OffsetObject* leftFire;
	OffsetObject* rightFire;
	OffsetObject* leftDuckFire;
	OffsetObject* rightDuckFire;
	// Camera
	Camera* camera;
	// Bullet
	std::vector<Bullet*> bullets;
	DWORD lastFire = 0;

	// Parameter
	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;
	float fireColdDown = 0.1f;
	// status
	bool move = false;
	bool right = true;
	bool air = true;
	bool shoot = false;
	bool duck = false;
	float verticalSpeed = 0.0f;

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
