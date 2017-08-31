
#ifndef _UI_OBJECT_H_
#define _UI_OBJECT_H_

class UIObject : public GameObject {
private:
	Camera* camera;

public:
	// offset
	Float2D offset;

	// Constructors
	UIObject(float offsetX, float offsetY, float sizeX, float sizeY);
	~UIObject();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
