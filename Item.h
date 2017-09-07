
#ifndef _ITEM_H_
#define _ITEM_H_

class Item : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// GameObject
	UIObject* info;

	// Constructors
	Item();
	~Item();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
