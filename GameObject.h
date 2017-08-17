
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

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
};

#endif
