
#ifndef _GROUND_H_
#define _GROUND_H_

class Ground : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// Animation

	// Parameter

	// Constructors
	Ground();
	~Ground();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
