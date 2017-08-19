
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class Animation {
private:
	int currentSprite;
	int sampleTime;
	int counter;

public:
	Int2D spriteSize;
	Int2D divide;
	int spriteMax;

	Sprite* sprite;

	Animation(int divideX, int divideY, int sampleTime);
	~Animation ();
	void MakeFrame();
	void SetTexture(Vertex2D* vertex);
};

#endif
