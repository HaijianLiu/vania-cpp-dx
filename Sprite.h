
#ifndef _SPRITE_H_
#define _SPRITE_H_

class Sprite {
private:
	Time* time;
	bool effect = false;
	DWORD startEffect = 0;
	bool flash = false;
	void Effect();

public:
	LPDIRECT3DDEVICE9 device;
	Vertex2D vertex[4] = {Vertex2D()};
	Texture texture;

	// Slice
	Slice slice;
	std::vector<Slice> frames;

	bool flipX = false;
	float flashTime = 0.5f;

	Sprite();
	~Sprite();

	// in Start function
	void MakeFrame(int frame, int x, int y, int w, int h);
	// in Update function
	void SetTexture(Vertex2D* vertex, int currentSprite);
	void SetTexture();

	void Draw();

	void Flash();
	void SetColor(int r, int g, int b, int a);

	#ifdef _DEBUG
		Sprite(int imageSizeX, int imageSizeY);
		void CreatTexture(const char* path);
		void SetTexture(Vertex2D* vertex);
		void Draw(Vertex2D* vertex);
	#endif
};

#endif
