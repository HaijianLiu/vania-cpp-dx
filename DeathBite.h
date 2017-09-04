
#ifndef _DEATH_BITE_H
#define _DEATH_BITE_H

class DeathBite : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// Animation
	Animation* animAppear;
	Animation* animDisappear;
	Animation* animBite;

	// Target
	GameObject* target;

	// Parameter
	float lastTime = 10.0f;
	float biteTime = 1.0f;

	// Status
	bool appear = false;
	bool bite = false;
	DWORD lastAppear = 0;
	DWORD lastBite = 0;
	float appearTime = 1.0f;

	// Constructors
	DeathBite();
	~DeathBite();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void Appear();
};

#endif
