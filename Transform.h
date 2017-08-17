
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

class Transform {
private:
	Camera* camera;

public:
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Transform ();
	virtual ~Transform ();

	void Update(Vertex2D* vertex, int sizeX, int sizeY);
	void Update(Vertex2D* vertex, Int2D size);
	void Update(Vertex2D* vertex, D3DXVECTOR2 size);
};

#endif
