
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player {
private:
	LPDIRECT3DDEVICE9  device;
	D3DXVECTOR3        position;
	D3DXVECTOR3        rotation;
	Vertex2D           vertex[4];

	Animation animRun;

	void SetTexture(int pattern);
	void SetVertex(void);

public:
	Player ();
	virtual ~Player ();
	void Start();
	void Update();
	void Draw();
};

#endif
