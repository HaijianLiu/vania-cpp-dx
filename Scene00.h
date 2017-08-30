
#ifndef _SCENE_00_H_
#define _SCENE_00_H_

class Scene00 : public Scene {
private:

public:
	std::vector<NoneObject*> playerPosition;

	// Enemy
	std::vector<Crab*> crabs;
	std::vector<Ground*> ai;
	std::vector<Block*> blocks;

	Scene00();
	~Scene00();

	void Start();
	void Update();

};

#endif
