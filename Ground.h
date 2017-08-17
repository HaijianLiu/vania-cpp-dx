
#ifndef _GROUND_H_
#define _GROUND_H_

class Ground : public GameObject {
private:
	std::vector<GameObject*>* gameObjects;

	Sprite* sprite;

public:
	BoxCollider* collider;

	Ground(Sprite* sprite);
	~Ground();

	void Start();
	void Update();
	void Draw();
	void OnTriggerEnter(BoxCollider* other);
	void OnTriggerExit(BoxCollider* other);
	// void OnTriggerStay(GameObject* other);
	// void OnTriggerLeave(GameObject* other);
};

#endif
