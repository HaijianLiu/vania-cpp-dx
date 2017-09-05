
#ifndef _BALL_H_
#define _BALL_H_

class Ball : public GameObject {
private:

public:
	// Collider
	BoxCollider* collGroundCheck;
	BoxCollider* collCeilingCheck;
	BoxCollider* collHorizonCheck;

	// GameObject
	Orb* orb;

	// Parameter
	float hp = 100.0f;
	float verticalSpeed = 1.0f;
	float horizonSpeed = 1.0f;

	// status
	bool up = false;
	bool right = false;

	// Constructors
	Ball ();
	~Ball();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
