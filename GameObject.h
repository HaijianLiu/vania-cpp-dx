
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

class BoxCollider;

class GameObject {
private:

public:
	Time* time;
	Transform* transform;
	Sprite* sprite;

	GameObject();
	~GameObject();

	void PreStart();
	void UpdateTransform();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnTriggerEnter(BoxCollider* other) = 0;
};

#endif
