
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Animation;

class Player {
private:
	LPDIRECT3DDEVICE9  device;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	Vertex2D vertex[4];

	LPDIRECT3DTEXTURE9 texture;
	Animation* animRun;

	void SetVertex(void);

public:
	Player ();
	virtual ~Player ();
	void Start();
	void Update();
	void Draw();
};

#endif
