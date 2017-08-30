
#ifndef _BLOCK_H_
#define _BLOCK_H_

class Block : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// Parameter
	int hp = 100;

	// Constructors
	Block();
	~Block();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
