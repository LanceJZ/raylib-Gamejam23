#pragma once
#include "Globals.h"
#include "Common.h"
#include "Utilities.h"
#include "Player.h"
#include "EnemyControl.h"
#include "Ore.h"

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	std::vector<Ore*> OreCollection;

	void SetCamera(Camera* cam);
	void SetPlayer(Player* thePlayer);
	void SetEnemies(EnemyControl* enemies);
	void SetOreModel(Model& model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Input();
	void Update();

	void SpawnOre(int amount, Vector3 position);

private:
	size_t RockSpawnTimer = 0;
	int RocksToSpawn = 0;

	Model OreModel = {};
	Camera* Cam = {};
	Player* ThePlayer = {};
	EnemyControl* Enemies = {};

	void PlayerOverEdge();
	void CameraUpdate();
	void CheckForOreToSpawn();
	void CheckToSpawnRocks();
};

