
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
	float gravity = 0.0f;
	Float2D startLifeTimeRange = Float2D(1.0f,3.0f);
	Float2D startSpeedRange = Float2D(0.05f,0.5f);
	Float2D startSizeRange = Float2D(0.01f,0.1f);
	bool sizeOverLifeTime = true;


	// status
	float startAngle;
	float startLifeTime;
	float startSpeed;
	float startSize;
	float sizeOverLife;

	// Constructors
	Particle();
	~Particle();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void Instantiate(Transform* transform);
};


#endif
