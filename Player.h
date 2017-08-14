
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Animation;

class Player {
private:
	LPDIRECT3DDEVICE9 device;
	Vertex2D vertex[4];

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float verticalSpeed = 0.0f;

	float gravity = 0.1f;
	float speed = 2.0f;
	float jumpPower = 5.0f;
	bool air = false;
	bool right = true;

	LPDIRECT3DTEXTURE9 texture;
	Animation* animRun;

	void SetVertex(void);

public:
	Player ();
	virtual ~Player();
	void Start();
	void Update();
	void Draw();
};

#endif
