
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

class SceneManager {
private:

public:
	// Camera
	Camera* camera;
	// Resources
	Resources* resources;

	// GameObject
	Player* player;
	
	// Scene
	unsigned int checkPoint = 0;
	unsigned int activeScene = 0;
	unsigned int gameOverScene = 0;
	std::vector<Scene*> scenes;

	SceneManager();
	~SceneManager();

	void Start();
	void Update();
	void Draw();

	// Functions
	void SetActiveScene(unsigned int i);
};

#endif
