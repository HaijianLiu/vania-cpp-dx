
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Score::Score() {
	// Set GameObject
	this->draw = false;
	// GameObject
	for (unsigned int i = 0; i < this->max; i++) {
		this->numbers.push_back(new UIObject(this->offset.x + (this->max - i - 1) * this->size.x, this->offset.y, (float)this->size.x, (float)this->size.y));
	}
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Score::~Score() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Score::Start() {
	// Resources
	for (unsigned int i = 0; i < this->numbers.size(); i++) {
		this->numbers[i]->active = false;
		this->numbers[i]->sprite->device = this->resources->device;
		this->numbers[i]->sprite->texture = this->resources->texUINumbers;
		this->numbers[i]->sprite->slice = Slice(0,0,0,this->size.x,this->size.y);
	}
	// show zero
	this->numbers[0]->active = true;

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Score::Update() {
	if (this->willAdd != 0) {
		this->score++;
		Score::AddOne(0);
		this->willAdd--;
	}

	// Animation SetTexture() || Sprite SetTexture()
}

void Score::AddOne(unsigned int i) {
	if (i < this->max) {
		if (this->numbers[i]->sprite->slice.position.x != 9 * this->size.x) {
			if (!this->numbers[i]->active) {
				this->numbers[i]->active = true;
			}
			this->numbers[i]->sprite->slice.position.x += this->size.x;
		}
		else {
			this->numbers[i]->sprite->slice.position.x = 0;
			Score::AddOne(i+1);
		}
	}
}

void Score::WillAdd(unsigned int i) {
	this->willAdd += i;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Score::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Score::FixedUpdate() {

}
