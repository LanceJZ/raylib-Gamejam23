#pragma once
#include "Globals.h"
#include "Common.h"
#include "Player.h"
#include "Base.h"
#include "EnemyOne.h"
#include "Rock.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<EnemyOne*> Ones;
	std::vector<Rock*> Rocks;
	Base* EnemyBase = {};

	void SetPlayer(Player* player);
	void SetEnemyBaseModels(Model& baseModel, Model& turretModel);
	void SetShotModel(Model& shotModel);
	void SetEnemyOneModel(Model& enemyModel);
	void SetRockModel(Model& rockModel);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

	void SpawnRocks(int amount);

private:
	Model EnemyBaseModel = {};
	Model EnemyBaseTurretModel = {};
	Model ShotModel = {};
	Model EnemyOneModel = {};
	Model RockModel = {};
	Player* ThePlayer = {};

	void Reset();

	void SpawnEnemyBase();
	void SpawnEnemyOne(int amount);

	Vector3 PositionAwayFromPlayer();
};

