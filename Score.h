
#ifndef _SCORE_H_
#define _SCORE_H_

class Score : public GameObject {
private:

public:
	// GameObject
	std::vector<UIObject*> numbers;

	// Score
	unsigned int score = 0;
	unsigned int willAdd = 0;

	// Spec
	Float2D offset = Float2D(140.0f,105.0f);
	Int2D size = Int2D(9,7);
	unsigned int max = 6;

	// Constructors
	Score();
	~Score();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	void AddOne(unsigned int i);
	void WillAdd(unsigned int i);
};

#endif
