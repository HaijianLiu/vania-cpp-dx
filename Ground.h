
#ifndef _GROUND_H_
#define _GROUND_H_

class Ground : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// Animation or Slice
	Slice slice;
	// Collider
	BoxCollider* collider;

	// Parameter

	// Constructors
	Ground();
	~Ground();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
};

#endif
