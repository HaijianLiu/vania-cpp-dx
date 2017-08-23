
#ifndef _BACK_GROUND_H_
#define _BACK_GROUND_H_

class BackGround : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// GameObject
	GameObject* gameObject;

	// Constructors
	BackGround();
	~BackGround();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
