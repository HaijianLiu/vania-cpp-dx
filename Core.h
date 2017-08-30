
#ifndef _CORE_H_
#define _CORE_H_

class BoxCollider;
class Resources;
class SceneManager;
class Camera;

struct Vertex2D {
	D3DXVECTOR3 vertex;
	float rhw;
	D3DCOLOR diffuse;
	D3DXVECTOR2 texCoord;
	Vertex2D() {
		this->rhw = 1.0f;
		this->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	};
};

struct Int2D {
	int x;
	int y;
	Int2D(){};
	Int2D(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct Float2D {
	float x;
	float y;
	Float2D(){};
	Float2D(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Texture {
	LPDIRECT3DTEXTURE9 texture;
	const char* path;
	Int2D size;
	Texture(){};
	Texture(const char* path, int x, int y) {
		this->texture = NULL;
		this->path = path;
		this->size = Int2D(x,y);
	}
};

struct Slice {
	int tileID;
	Int2D position;
	Int2D size;
	Slice() {};
	Slice(int tileID, int x, int y, int w, int h) {
		this->tileID = tileID;
		this->position = Int2D(x,y);
		this->size = Int2D(w,h);
	}
};


#endif
