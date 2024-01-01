#pragma once
#include "Globals.h"
#include "Common.h"
#include "Player.h"
#include "Base.h"
#include "EnemyOne.h"
#include "EnemyTwo.h"
#include "Rock.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<EnemyOne*> Ones;
	std::vector<EnemyTwo*> Twos;
	std::vector<Rock*> Rocks;
	Base* EnemyBase = {};

	void SetPlayer(Player* player);
	void SetEnemyBaseModel(Model& model);
	void SetEnemyBaseTurretModel(Model& model);
	void SetShotModel(Model& model);
	void SetEnemyOneModel(Model& model);
	void SetEnemyTwoModel(Model& model);
	void SetRockModel(Model& model);
	void SetArrowModel(Model& model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

	void SpawnRocks(int amount);

private:
	Model EnemyBaseModel = {};
	Model EnemyBaseTurretModel = {};
	Model ShotModel = {};
	Model EnemyOneModel = {};
	Model EnemyTwoModel = {};
	Model RockModel = {};
	Model ArrowModel = {};

	Player* ThePlayer = {};

	void Reset();

	void SpawnEnemyBase();
	void SpawnEnemyOne(int amount);
	void SpawnEnemyTwo(int amount);

	Vector3 PositionAwayFromPlayer();
};

