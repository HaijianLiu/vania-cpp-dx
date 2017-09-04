
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

	// Status
	bool appear = false;
	bool bite = false;

	// Constructors
	DeathBite();
	~DeathBite();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
