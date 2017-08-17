
#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

class GameObject {
private:
	/* data */

public:
	GameObject();
	virtual ~GameObject();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#endif
