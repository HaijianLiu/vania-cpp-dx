
#ifndef _GROUND_H_
#define _GROUND_H_

class Ground : public GameObject {
private:
	std::vector<GameObject*>* gameObjects;

	Vertex2D vertex[4] = {Vertex2D()};
	Sprite* sprite;

public:
	Transform* transform;
	BoxCollider* collider;

	Ground(Sprite* sprite);
	~Ground();

	void Start();
	void Update();
	void Draw();
};

#endif
