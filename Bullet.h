
#ifndef _BULLET_H_
#define _BULLET_H_

class Bullet : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// Parameter
	float speed = 3.0f;
	float lifeTime = 1.0f;

	// status
	bool right = true;
	D3DXVECTOR3 lastPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Constructors
	Bullet();
	~Bullet();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
};

#endif
