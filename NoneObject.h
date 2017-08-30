
#ifndef _NONE_OBJECT_H_
#define _NONE_OBJECT_H_

class NoneObject : public GameObject {
private:

public:
	// Constructors
	NoneObject();
	~NoneObject();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
