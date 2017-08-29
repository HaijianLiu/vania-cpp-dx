
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

class BoxCollider;

class GameObject {
private:

public:
	Time* time;
	Transform* transform;
	Sprite* sprite;
	bool active = true;
	bool draw = true;
	DWORD birthTime = 0;

	GameObject();
	virtual ~GameObject();

	void PreStart();
	void UpdateTransform();
	void Draw();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void OnTriggerEnter(BoxCollider* other) = 0;
};

#endif
