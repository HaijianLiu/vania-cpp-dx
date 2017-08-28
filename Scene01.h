﻿
#ifndef _SCENE_01_H_
#define _SCENE_01_H_

class Scene01 : public Scene {
private:

public:
	// Map Data
	std::vector<int> cameraData;
	std::vector<int> groundData;
	std::vector<int> backGroundData;
	std::vector<int> rangeData;
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;
	std::vector<NoneObject*> range;

	Scene01();
	~Scene01();

	void Start();
	void Update();

};

#endif
