
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player : public GameObject {
private:
	std::vector<GameObject*>* gameObjects;
	
	Time* time;

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
	Vertex2D vertex[4] = {Vertex2D()};

	// Transform
	Transform* transform;

	bool air = false;
	float verticalSpeed = 0.0f;

	// Collider
	BoxCollider* collGroundCheck;

	Player ();
	~Player();

	void Start();
	void Update();
	void Draw();
};

#endif
