
#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class Animation {
private:
	int currentPattern;
	int patternMax;
	int sampleTime;
	int counter;

	void SetTexture(Vertex2D* vertex);

public:
	int patterSizeX, patterSizeY;
	int divideX, divideY;
	bool flipX;

	Animation(int imageSizeX, int imageSizeY, int divideX, int divideY, int sampleTime);
	virtual ~Animation ();
	void Update(Vertex2D* vertex);
};

#endif
