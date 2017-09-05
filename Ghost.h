
#ifndef _GHOST_H_
#define _GHOST_H_

class Ghost : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// Animation
	Animation* animation;

	// GameObject
	GameObject* target;

	// Constructors
	Ghost();
	~Ghost();

	// Parameter
	float hp = 100.0f;
	float speed = 0.3f;

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
