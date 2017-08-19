
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

public:
	Vertex2D vertex[4] = {Vertex2D()};
	Texture texture;

	// Slice
	std::vector<Slice> frames;
	std::map<const char*, Slice> slices;

	bool flipX = false;

	Sprite();
	~Sprite();

	void MakeSlice(Slice slice);
	void MakeFrame(int frame, int x, int y, int w, int h);

	void SetTexture(Vertex2D* vertex, int currentSprite);
	void SetTexture(Vertex2D* vertex, const char* name);

	void Draw(Vertex2D* vertex);

	#ifdef _DEBUG
		Sprite(int imageSizeX, int imageSizeY);
		void CreatTexture(const char* path);
		void SetTexture(Vertex2D* vertex);
	#endif
};

#endif
