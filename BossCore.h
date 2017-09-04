
#ifndef _BOSS_CORE_H_
#define _BOSS_CORE_H_

class BossCore : public GameObject {
private:

public:
	// GameObject
	GameObject* parent;
	GameObject* target;

	// Parameter
	float radius = 0.1f;
	float speed = 0.5f;

	// Constructors
	BossCore ();
	~BossCore();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void FollowTarget();
	void LookRight();
	void LookLeft();
};

#endif
