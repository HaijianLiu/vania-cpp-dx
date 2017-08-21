
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
	Animation* animRun;
	Animation* animJump;
	// Camera
	Camera* camera;

	// Parameter
	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;
	bool move = false;
	bool right = true;
	bool air = true;
	float verticalSpeed = 0.0f;

	// Constructors
	Player ();
	~Player();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
};

#endif
