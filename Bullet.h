
#ifndef _BULLET_H_
#define _BULLET_H_

class Bullet : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// GameObject
	GameObject* gameObject;
	// Collider
	BoxCollider* collider;
	// Animation

	// Parameter
	float speed = 3.0f;
	float lifeTime = 2.0f;

	// status
	bool right = true;
	DWORD birthTime;

	// Constructors
	Bullet();
	~Bullet();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void Destroy(GameObject* gameObject, float time);
};

#endif
