
#ifndef _BOSS_H_
#define _BOSS_H_

enum skill { NONE_SKILL, DEATH_AREA_LEFT, DEATH_AREA_RIGHT, SKILL_MAX };

class Boss : public GameObject {
private:

public:
	// Camera
	Camera* camera;

	// Collider
	BoxCollider* collider;
	// OffsetObject
	OffsetObject* leftTarget;
	OffsetObject* rightTarget;

	// GameObject
	BossCore* core;
	std::vector<DeathWall*> deathWallsLeft;
	std::vector<DeathWall*> deathWallsRight;
	std::vector<BossBullet*> bullets;
	// UIObject
	UIObject* uiBossBG;
	UIObject* uiLife;

	// Target
	GameObject* target;

	// Parameter
	float hp = 1000.0f;
	float deathWallRange = 1.6f;
	float skillColdDown = 10.0f;
	float bulletColdDown = 15.0f;

	// status
	bool awake = false;
	bool freeze = true;
	bool intro = false;
	int currentSkill = NONE_SKILL;
	DWORD lastSkill = 0;
	DWORD lastBullet = 0;

	// Constructors
	Boss ();
	~Boss();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();

	// Functions
	void CheckSkill();
};

#endif
