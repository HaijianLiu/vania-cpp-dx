
#ifndef _DEATH_WALL_H_
#define _DEATH_WALL_H_

class DeathWall : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// Constructors
	DeathWall();
	~DeathWall();

	// Parameter
	float speed = 1.0f;
	float maxArea = 1.6f;

	// status
	D3DXVECTOR3 startPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bool right = true;
	float maxDistance = 0.32f;

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void Forward();
	void DeathArea(bool right);
};

#endif
