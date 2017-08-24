
#ifndef _CRAB_H_
#define _CRAB_H_

class Crab : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// GameObject
	GameObject* gameObject;
	// Collider
	BoxCollider* collGroundCheck;
	BoxCollider* collHorizonCheck;
	// Animation
	Animation* animWalk;

	// Parameter
	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;

	// status
	bool move = false;
	bool right = true;
	bool air = true;
	float verticalSpeed = 0.0f;

	// Constructors
	Crab ();
	~Crab();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
