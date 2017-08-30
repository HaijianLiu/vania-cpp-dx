
#ifndef _ANIMATION_OBJECT_H_
#define _ANIMATION_OBJECT_H_

class AnimationObject : public GameObject {
private:

public:
	// Animation
	Animation* animation;
	bool loop = false;

	// Constructors
	AnimationObject(int sizeX, int sizeY, int divideX, int divideY, int sampleTime);
	~AnimationObject();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// for Instantiate
	void Reset();
};

#endif
