
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

class GameObject {
private:
	// List of GameObjects
	std::vector<GameObject*>* gameObjects;

public:
	// Global class
	Time* time;
	Resources* resources;
	// function class
	Transform* transform;
	Sprite* sprite;
	Status* status;
	// status
	DWORD birthTime = 0;
	bool active = true;
	bool draw = true;

	GameObject();
	virtual ~GameObject();

	void PreStart();
	void UpdateTransform();
	void Draw();
	void Reset();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void OnTriggerEnter(BoxCollider* other) = 0;
};

#endif
