
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player : public GameObject {
private:
	std::vector<GameObject*>* gameObjects;

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

public:
	// Collider
	BoxCollider* collGroundCheck;

	bool air = false;
	float verticalSpeed = 0.0f;

	Player ();
	~Player();

	void Start();
	void Update();
	void Draw();
	void OnTriggerEnter(BoxCollider* other);
	void OnTriggerExit(BoxCollider* other);
	// void OnTriggerStay(GameObject* other);
	// void OnTriggerLeave(GameObject* other);
};

#endif
