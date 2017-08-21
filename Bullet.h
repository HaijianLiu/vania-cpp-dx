
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
	float lifeTime = 2.0f;

	// status
	DWORD birthTime;

	// Constructors
	Bullet();
	~Bullet();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);

	// Functions
	void Destroy(GameObject* gameObject, float time);
};

#endif
