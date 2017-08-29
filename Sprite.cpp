
#include "Engine.h"

Sprite::Sprite() {
	this->time = GetTime();
}
Sprite::~Sprite() {

}


void Sprite::MakeFrame(int frame, int x, int y, int w, int h) {
	this->frames.push_back(Slice(0,x,y,w,h));
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
void Sprite::SetTexture() {
	float x = (float)this->slice.position.x / (float)this->texture.size.x;
	float y = (float)this->slice.position.y / (float)this->texture.size.y;
	float w = (float)this->slice.size.x / (float)this->texture.size.x;
	float h = (float)this->slice.size.y / (float)this->texture.size.y;;

	if (this->flipX == false) {
		this->vertex[0].texCoord = D3DXVECTOR2(x,y);
		this->vertex[1].texCoord = D3DXVECTOR2(x+w,y);
		this->vertex[2].texCoord = D3DXVECTOR2(x,y+h);
		this->vertex[3].texCoord = D3DXVECTOR2(x+w,y+h);
	}
	if (this->flipX == true) {
		this->vertex[0].texCoord = D3DXVECTOR2(x+w,y);
		this->vertex[1].texCoord = D3DXVECTOR2(x,y);
		this->vertex[2].texCoord = D3DXVECTOR2(x+w,y+h);
		this->vertex[3].texCoord = D3DXVECTOR2(x,y+h);
	}
}

void Sprite::Draw() {
	Sprite::Effect();
	this->device->SetFVF(FVF_VERTEX_2D);
	this->device->SetTexture(0,this->texture.texture);
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, this->vertex, sizeof(Vertex2D));
}


void Sprite::Effect() {
	if (this->effect) {
		if (this->flash) {
			if (this->time->currentTime < this->startEffect + this->flashTime * 1000.0f) {
				if (this->time->currentTime % 200 < 100) {
					this->vertex[0].diffuse = D3DCOLOR_RGBA(0,0,0,255);
					this->vertex[1].diffuse = D3DCOLOR_RGBA(0,0,0,255);
					this->vertex[2].diffuse = D3DCOLOR_RGBA(0,0,0,255);
					this->vertex[3].diffuse = D3DCOLOR_RGBA(0,0,0,255);
				}
				else {
					this->vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
					this->vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
					this->vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
					this->vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
				}
			}
			else {
				this->vertex[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
				this->vertex[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
				this->vertex[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
				this->vertex[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
				this->effect = false;
				this->flash = false;
			}
		}
	}
}

void Sprite::Flash() {
	this->effect = true;
	this->flash = true;
	this->startEffect = this->time->currentTime;
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
