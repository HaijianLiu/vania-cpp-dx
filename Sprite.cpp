
#include "Engine.h"

Sprite::Sprite() {

}
Sprite::~Sprite() {
	
}

void Sprite::MakeSlice(Slice slice) {
	this->slices.insert(std::make_pair(slice.name, slice));
}

void Sprite::MakeFrame(int frame, int x, int y, int w, int h) {
	this->frames.push_back(Slice("frame",x,y,w,h));
}

void Sprite::SetTexture(Vertex2D* vertex, int currentSprite) {
	float x = (float)this->frames[currentSprite].position.x / (float)this->texture.size.x;
	float y = (float)this->frames[currentSprite].position.y / (float)this->texture.size.y;
	float w = (float)this->frames[currentSprite].size.x / (float)this->texture.size.x;
	float h = (float)this->frames[currentSprite].size.y / (float)this->texture.size.y;;

	if (this->flipX == false) {
		(vertex+0)->texCoord = D3DXVECTOR2(x,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x+w,y+h);
	}
	if (this->flipX == true) {
		(vertex+0)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x+w,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x,y+h);
	}
}
void Sprite::SetTexture(Vertex2D* vertex, const char* name) {
	float x = (float)this->slices.at(name).position.x / (float)this->texture.size.x;
	float y = (float)this->slices.at(name).position.y / (float)this->texture.size.y;
	/* inver y axis
	float y = (float)(this->texture.size.y - this->slices.at(name).position.y - this->slices.at(name).size.y) / (float)this->texture.size.y;
	*/
	float w = (float)this->slices.at(name).size.x / (float)this->texture.size.x;
	float h = (float)this->slices.at(name).size.y / (float)this->texture.size.y;;

	if (this->flipX == false) {
		(vertex+0)->texCoord = D3DXVECTOR2(x,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x+w,y+h);
	}
	if (this->flipX == true) {
		(vertex+0)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x+w,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x,y+h);
	}
}

void Sprite::Draw() {
	this->device->SetFVF(FVF_VERTEX_2D);
	this->device->SetTexture(0,this->texture.texture);
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, this->vertex, sizeof(Vertex2D));
}



#ifdef _DEBUG
	Sprite::Sprite(int imageSizeX, int imageSizeY) {
		this->texture.size = Int2D(imageSizeX, imageSizeY);
	}

	void Sprite::CreatTexture(const char* path) {
		this->device = GetDevice();

		D3DXCreateTextureFromFileEx(
			this->device, path,
			this->texture.size.x, this->texture.size.y,
			1, 0,
			D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
			&this->texture.texture);
	}

	void Sprite::SetTexture(Vertex2D* vertex) {
		if (this->flipX == false) {
			(vertex+0)->texCoord = D3DXVECTOR2(0.0f, 0.0f);
			(vertex+1)->texCoord = D3DXVECTOR2(1.0f, 0.0f);
			(vertex+2)->texCoord = D3DXVECTOR2(0.0f, 1.0f);
			(vertex+3)->texCoord = D3DXVECTOR2(1.0f, 1.0f);
		}
		if (this->flipX == true) {
			(vertex+0)->texCoord = D3DXVECTOR2(1.0f, 0.0f);
			(vertex+1)->texCoord = D3DXVECTOR2(0.0f, 0.0f);
			(vertex+2)->texCoord = D3DXVECTOR2(1.0f, 1.0f);
			(vertex+3)->texCoord = D3DXVECTOR2(0.0f, 1.0f);
		}
	}
	void Sprite::Draw(Vertex2D* vertex) {
		this->device->SetFVF(FVF_VERTEX_2D);
		this->device->SetTexture(0,this->texture.texture);
		this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
	}
#endif
