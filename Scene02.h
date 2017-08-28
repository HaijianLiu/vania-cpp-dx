
#ifndef _SCENE_02_H_
#define _SCENE_02_H_

class Scene02 : public Scene {
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

	Scene02();
	~Scene02();

	void Start();
	void Update();

};

#endif
