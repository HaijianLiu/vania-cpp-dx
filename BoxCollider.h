
#ifndef _BOX_COLLIDER_H_
#define _BOX_COLLIDER_H_

class BoxCollider {
private:

	#ifdef _DEBUG
		// for Render
		Vertex2D vertex[4] = {Vertex2D()};
		Transform* transform;
		Sprite* sprite;
	#endif

public:
	Transform* parent;
	D3DXVECTOR2 offset;
	D3DXVECTOR2 size;

	bool trigger = false;
	bool enter = false;

	BoxCollider(Transform* parent, float x, float y, float w, float h);
	virtual ~BoxCollider();

	#ifdef _DEBUG
		// for render
		void Start();
		void Update();
		void Draw();
	#endif
};

#endif
