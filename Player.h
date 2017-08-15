
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Animation;

class Player {
private:
	LPDIRECT3DDEVICE9 device;
	Vertex2D vertex[4];
	Time* time;

	LPDIRECT3DTEXTURE9 texture;
	Transform* transform;
	Animation* animRun;

	float gravity = 9.8f;
	float speed = 1.0f;
	float jumpPower = 4.0f;
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
