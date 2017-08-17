
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

class BoxCollider;

class GameObject {
private:

public:
	Time* time;
	Vertex2D vertex[4] = {Vertex2D()};
	Transform* transform;

	GameObject();
	~GameObject();

	void PreStart();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnTriggerEnter(GameObject* other) = 0;
	virtual void OnTriggerExit(GameObject* other) = 0;
	// virtual void OnTriggerStay(GameObject* other) = 0;
	// virtual void OnTriggerLeave(GameObject* other) = 0;
	virtual BoxCollider* GetCollider();
};

#endif
