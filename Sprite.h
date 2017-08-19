
#ifndef _SPRITE_H_
#define _SPRITE_H_

struct Slice {
	const char* name;
	Int2D position;
	Int2D size;
	Slice() {};
	Slice(const char* name, int x, int y, int w, int h) {
		this->name = name;
		this->position = Int2D(x,y);
		this->size = Int2D(w,h);
	}
};

class Sprite {
private:
	LPDIRECT3DDEVICE9 device;
	Texture texture;

public:
	// Animation
	Int2D spriteSize;
	Int2D divide;
	int spriteMax;
	// Slice
	std::map<const char*, Slice> slices;

	bool flipX = false;

	Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY);
	Sprite(int imageSizeX, int imageSizeY);
	virtual ~Sprite();

	void CreatTexture(const char* path);
	void MakeSlice(Slice slice);
	void SetTexture(Vertex2D* vertex);
	void SetTexture(Vertex2D* vertex, int currentSprite);
	void SetTexture(Vertex2D* vertex, const char* name);
	void Draw(Vertex2D* vertex);
};

#endif
