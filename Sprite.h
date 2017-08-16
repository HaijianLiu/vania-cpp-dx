
#ifndef _SPRITE_H_
#define _SPRITE_H_

struct Slice {
	Int2D position;
	Int2D size;
	Slice() {};
	Slice(int x, int y, int w, int h) {
		this->position = Int2D(x,y);
		this->size = Int2D(w,h);
	}
};

class Sprite {
private:
	LPDIRECT3DDEVICE9 device;
	LPDIRECT3DTEXTURE9 texture;

	Int2D imageSize;

public:
	Int2D spriteSize;
	Int2D divide;
	int spriteMax;

	std::map<const char*, Slice> slices;

	bool flipX = false;

	Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY);
	Sprite(int imageSizeX, int imageSizeY);
	virtual ~Sprite();

	void CreatTexture(const char* path);
	void MakeSlice(const char* name, int x, int y, int w, int h);
	void SetTexture(Vertex2D* vertex, int currentSprite);
	void SetTexture(Vertex2D* vertex, const char* name);
	void Draw(Vertex2D* vertex);
};

#endif
