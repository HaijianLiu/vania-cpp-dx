
#ifndef _BOX_COLLIDER_H_
#define _BOX_COLLIDER_H_

class BoxCollider {
private:
	D3DXVECTOR2 offset;
	D3DXVECTOR2 size;

	#ifdef _DEBUG
		Vertex2D vertex[4] = {Vertex2D()};
		Transform* transform;
		Sprite* sprite;
	#endif

public:
	BoxCollider(float x, float y, float w, float h);
	virtual ~BoxCollider();


	#ifdef _DEBUG
		void Start();
		void Update(Transform* transform);
		void Draw();
	#endif
};

#endif
