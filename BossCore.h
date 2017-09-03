
#ifndef _BOSS_CORE_H_
#define _BOSS_CORE_H_

class BossCore : public GameObject {
private:

public:
	// Parameter
	float radius = 0.1f;

	// Constructors
	BossCore ();
	~BossCore();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
