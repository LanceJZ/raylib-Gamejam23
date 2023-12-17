#include "EnemyControl.h"

EnemyControl::EnemyControl()
{

}

EnemyControl::~EnemyControl()
{
}

void EnemyControl::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void EnemyControl::SetShotModel(Model& shotModel)
{
	ShotModel = ShotModel;
}

void EnemyControl::SetEnemyOneModel(Model& enemyModel)
{
	EnemyOneModel = EnemyOneModel;
}

bool EnemyControl::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool EnemyControl::BeginRun()
{
	SpawnEnemyOne(10);

	return false;
}

void EnemyControl::Update()
{

}

void EnemyControl::SpawnEnemyOne(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = Ones.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!Ones[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}

			if (spawnNew)
			{
				//When adding as a new class, make sure to use DBG_NEW.
				Ones.push_back(DBG_NEW EnemyOne());
				TheManagers.EM.AddModel3D(Ones[spawnNumber], *EnemyOneModel);
				Ones[spawnNumber]->Initialize(TheUtilities);
				Ones[spawnNumber]->BeginRun();
			}

			Vector3 spawnPosition = {};


			Ones[spawnNumber]->Spawn(spawnPosition);
		}
	}
}
