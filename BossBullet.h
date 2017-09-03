
#ifndef _BOSS_BULLET_H_
#define _BOSS_BULLET_H_

class BossBullet : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// Animation
	Animation* animation;

	// GameObject
	GameObject* target;

	// Constructors
	BossBullet();
	~BossBullet();

	// Parameter
	float hp = 40.0f;
	float speed = 0.3f;

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
