
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// Collider
	BoxCollider* collGroundCheck;
	// Animation
	Animation* animIdle;
	Animation* animRun;
	Animation* animJump;

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
	void Draw();
	void OnTriggerEnter(BoxCollider* other);
};

#endif
