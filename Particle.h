
#ifndef _PARTICLE
#define _PARTICLE

class Particle : public GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// GameObject
	GameObject* gameObject;

	// Parameter
	float speed = 3.0f;
	float lifeTime = 2.0f;

	// status
	bool right = true;
	DWORD birthTime;

	// Constructors
	Particle();
	~Particle();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void Destroy(GameObject* gameObject, float time);
};


#endif
