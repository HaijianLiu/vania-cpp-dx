
#ifndef _JUMPER_H_
#define _JUMPER_H_

class Jumper : public GameObject {
private:

public:
	// Collider
	BoxCollider* collGroundCheck;
	BoxCollider* collCeilingCheck;
	BoxCollider* collHorizonCheck;
	// Animation
	Animation* animIdle;
	Animation* animJump;
	AnimationObject* enemyDestroy;

	// GameObject
	Orb* orb;

	// Parameter
	float gravity = 9.8f;
	float speed = 0.5f;
	float jumpPower = 4.0f;
	float jumpColdDown = 1.0f;

	// status
	bool right = false;
	bool air = true;
	float verticalSpeed = 0.0f;
	DWORD lastJump = 0;

	// Constructors
	Jumper ();
	~Jumper();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
