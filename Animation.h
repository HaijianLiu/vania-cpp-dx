
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class Animation {
private:
	int currentSprite;
	int sampleTime;
	int counter;

public:
	Sprite* sprite;

	Animation(int imageSizeX, int imageSizeY, int divideX, int divideY, int sampleTime);
	virtual ~Animation ();
	void Update(Vertex2D* vertex);
};

#endif
