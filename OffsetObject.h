
#ifndef _OFFSET_OBJECT_H_
#define _OFFSET_OBJECT_H_

class OffsetObject : public GameObject {
private:

public:
	GameObject* parent;
	Float2D offset;

	// Constructors
	OffsetObject(GameObject* parent, float x, float y);
	~OffsetObject();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
