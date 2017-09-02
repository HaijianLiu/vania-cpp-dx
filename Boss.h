
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
	// UIObject
	UIObject* uiBossBG;
	UIObject* uiLife;

	// Target
	GameObject* target;

	// Parameter
	float hp = 1000.0f;

	// status
	bool awake = false;
	bool freeze = true;

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
