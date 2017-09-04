﻿
#ifndef _CHECK_POINT_H_
#define _CHECK_POINT_H_

class CheckPoint : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;

	// Constructors
	CheckPoint();
	~CheckPoint();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
