
#ifndef _BOX_COLLIDER_H_
#define _BOX_COLLIDER_H_

class BoxCollider {
private:
	std::vector<BoxCollider*>* colliders;

	#ifdef _DEBUG
		// for Render
		Vertex2D vertex[4] = {Vertex2D()};
		Transform* transform;
		Sprite* sprite;
	#endif

public:
	GameObject* gameObject;
	D3DXVECTOR2 offset;
	D3DXVECTOR2 size;
	D3DXVECTOR2 halfSize;

	bool trigger = false; // if check collision with others
	bool active = true; // if check collision
	bool enter = false; // will be set to true before OnTriggerEnter and be set to false after OnTriggerEnter

	BoxCollider(GameObject* gameObject, float x, float y, float w, float h);
	~BoxCollider();

	#ifdef _DEBUG
		// for render
		void Start();
		void Update();
		void Draw();
	#endif
};

#endif
