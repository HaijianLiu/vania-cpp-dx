
#ifndef _SCENE_H_
#define _SCENE_H_

class Scene {
private:
	// global GameObjects and Colliders parameter
	std::vector<GameObject*>* gpGameObjects;
	std::vector<BoxCollider*>* gpColliders;
	unsigned int startGameObjectsSize;
	unsigned int startCollidersSize;

public:
	// Scene GameObjects and Colliders
	std::vector<GameObject*> gameObjects;
	std::vector<BoxCollider*> colliders;
	// SceneManager
	SceneManager* sceneManager;
	// Camera
	Camera* camera;
	// Camera
	Time* time;

	// Frame Delay
	bool frameDelay = true; // skip the first frame

	// Map Data
	Int2D mapSize = Int2D(225,90);
	int tilePixel = 16;
	Int2D tileSize = Int2D(384/16,320/16);
	// Map path
	const char* cameraPath = "map/scene_Scene-Null";
	const char* rangePath = "map/scene_Scene-Null";
	const char* bossPath = "map/scene_Scene-Null";
	const char* ballPath = "map/scene_Scene-Null";
	const char* ghostPath = "map/scene_Scene-Null";
	const char* jumperPath = "map/scene_Scene-Null";
	const char* flyerPath = "map/scene_Scene-Null";
	const char* crabPath = "map/scene_Scene-Null";
	const char* aiPath = "map/scene_Scene-Null";
	const char* orbPath = "map/scene_Scene-Null";
	const char* blockPath = "map/scene_Scene-Null";
	const char* itemPath = "map/scene_Scene-Null";
	const char* playerPath = "map/scene_Scene-Null";
	const char* damageZonePath = "map/scene_Scene-Null";
	const char* groundPath = "map/scene_Scene-Null";
	const char* backGroundPath = "map/scene_Scene-Null";
	const char* backGround2Path = "map/scene_Scene-Null";
	// ReSet Data
	std::vector<Int2D> ballData;
	std::vector<Int2D> ghostData;
	std::vector<Int2D> jumperData;
	std::vector<Int2D> flyerData;
	std::vector<Int2D> crabData;
	std::vector<Int2D> playerData;
	// Map Object
	CheckPoint* checkPoint;
	std::vector<NoneObject*> range;
	std::vector<Boss*> bosses;
	std::vector<Ball*> balls;
	std::vector<Ghost*> ghosts;
	std::vector<Jumper*> jumpers;
	std::vector<Flyer*> flyers;
	std::vector<Crab*> crabs;
	std::vector<Ground*> ai;
	std::vector<Item*> items;
	std::vector<Orb*> orbs;
	std::vector<Block*> blocks;
	std::vector<DamageZone*> damageZones;
	std::vector<Ground*> grounds;
	std::vector<BackGround*> backGrounds;
	// BackGround Object
	UIObject* backGround2nd;
	UIObject* backGround4th;

	Scene();
	virtual ~Scene();

	virtual void Start();
	void SetScene();
	virtual void Update();
	void Draw();

	// Functions
	bool CheckCollision(BoxCollider* a, BoxCollider* b);
	void CheckCollider();
	bool LoadMapData(const char* path, std::vector<Int2D>& data);
	void SetTile(GameObject* gameObject, int mapID, int tileID);
	void SetPosition(GameObject* gameObject, int mapID);
	void Reset();
};

#endif
