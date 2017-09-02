
#ifndef _DAMAGE_ZONE_H_
#define _DAMAGE_ZONE_H_

class DamageZone : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// Constructors
	DamageZone();
	~DamageZone();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
