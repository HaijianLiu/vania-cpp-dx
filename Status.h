
#ifndef _STATUS_H_
#define _STATUS_H_

class Status {
private:
	/* data */

public:
	float hp = 0;
	float damage = 0;
	const char* tag = "none";

	Status();
	~Status();
};

#endif
