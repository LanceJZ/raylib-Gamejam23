#pragma once
#include "Globals.h"
#include "Common.h"
#include "Managers.h"
#include "Player.h"
#include "EnemyOne.h"

class EnemyControl : public Common
{
public:
	EnemyControl();
	virtual ~EnemyControl();

	std::vector<EnemyOne*> Ones;

	void SetPlayer(Player* player);
	void SetShotModel(Model& shotModel);
	void SetEnemyOneModel(Model& enemyModel);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:
	Model* ShotModel = {};
	Model* EnemyOneModel = {};
	Player* ThePlayer = {};

	void SpawnEnemyOne(int amount);
};

