﻿
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

	bool trigger = false;
	bool enter = false;
	bool exit = false;
	bool stay = false;

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
