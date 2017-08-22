
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
	Float2D startLifeTimeRange = Float2D(0.2f,0.5f);
	Float2D startSpeedRange = Float2D(0.1f,1.0f);
	Float2D startSizeRange = Float2D(0.01f,0.1f);
	Float2D startAngleRange = Float2D(0.0f,2.0f*PI);

	// status
	float gravity = 1.5f;
	float verticalSpeed = 0.0f;
	bool sizeOverLifeTime = true;
	float startLifeTime;
	float startSpeed;
	float startSize;
	float startAngle;

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
