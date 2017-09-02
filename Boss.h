
#ifndef _BOSS_H_
#define _BOSS_H_

class Boss : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// Animation

	// GameObject
	BossCore* core;

	// Target
	GameObject* target;

	// Parameter

	// status

	// Constructors
	Boss ();
	~Boss();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
