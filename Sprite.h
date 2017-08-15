
#ifndef _SPRITE_H_
#define _SPRITE_H_

class Sprite {
private:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DTEXTURE9 texture;

	Int2D imageSize;

public:
	Int2D spriteSize;
	Int2D divide;
	int spriteMax;
	bool flipX = false;

	Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY);
	virtual ~Sprite();

	void CreatTexture(const char* path);
	void SetTexture(Vertex2D* vertex, int currentSprite);
	void Draw(Vertex2D* vertex);
};

#endif
