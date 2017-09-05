
#ifndef _BOSS_H_
#define _BOSS_H_

enum skill { DEATH_BITE, DEATH_AREA, SKILL_MAX, NONE_SKILL, DEATH_AREA_LEFT, DEATH_AREA_RIGHT };

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
	DeathBite* deathBite;
	// UIObject
	UIObject* uiBossBG;
	UIObject* uiLife;

	// Target
	GameObject* target;

	// Parameter
	float sleepHP = 100.0f;
	float hp = 1500.0f;
	float deathWallRange = 1.6f;
	float deathAreaTime = 3.0f;
	float deathBiteTime = 2.0f;
	float skillColdDown = 5.0f;
	float skillDelay = 1.0f;
	float bulletColdDown = 15.0f;

	// status
	bool awake = false;
	bool intro = false;
	int currentSkill = NONE_SKILL;
	DWORD lastSkill = 0;
	DWORD lastBullet = 0;
	int phase = 0;

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
