
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Animation;

class Player {
private:
	LPDIRECT3DDEVICE9 device;
	Vertex2D vertex[4];

	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float speed = 5.0f;

	LPDIRECT3DTEXTURE9 texture;
	Animation* animRun = new Animation(800,80,10,1,4);

	void SetVertex(void);

public:
	Player ();
	virtual ~Player ();
	void Start();
	void Update();
	void Draw();
};

#endif
