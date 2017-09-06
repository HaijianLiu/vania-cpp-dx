
#ifndef _SCORE_H_
#define _SCORE_H_

class Score : public GameObject {
private:
	Camera* camera;

public:
	// offset
	Float2D offset;

	// Constructors
	Score(float offsetX, float offsetY, float sizeX, float sizeY);
	~Score();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
