
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Animation;

class Player {
private:
	Vertex2D vertex[4];
	Time* time;

	Transform* transform;

	Animation* animIdle;
	Animation* animRun;
	Animation* animJump;

	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;
	bool move = false;
	bool air = false;
	bool right = true;


public:
	float verticalSpeed = 0.0f;

	Player ();
	virtual ~Player();
	void Start();
	void Update();
	void Draw();
};

#endif
