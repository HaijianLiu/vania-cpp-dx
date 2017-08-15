
#ifndef _SPRITE_H_
#define _SPRITE_H_

class Sprite {
private:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DTEXTURE9 texture;

	D3DXVECTOR2 imageSize;
	D3DXVECTOR2 divide;
	D3DXVECTOR2 spriteSize;
	int spriteMax;

public:
	bool flipX = false;

	Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY);
	virtual ~Sprite();

	void CreatTexture(const char* path);
};

#endif
