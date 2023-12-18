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
	EnemyOneModel = &enemyModel;
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
		float minX = 0;
		float maxX = 0;
		float minY = 0;
		float maxY = 0;

		if (ThePlayer->X() < (-FieldSize.x + GetScreenWidth()))
		{
			minX = ThePlayer->X() + GetScreenWidth();
			maxX = FieldSize.x;
		}
		else if (ThePlayer->X() > (FieldSize.x - GetScreenWidth()))
		{
			minX = FieldSize.x - GetScreenWidth();
			maxX = -ThePlayer->X() + GetScreenWidth();
		}
		else
		{
			if (GetRandomValue(1, 10 > 5))
			{
				minX = -FieldSize.x;
				maxX = -ThePlayer->X() - GetScreenWidth();
			}
			else
			{
				minX = ThePlayer->X() + GetScreenWidth();
				maxX = FieldSize.x;
			}

		}

		if (ThePlayer->Y() < (-FieldSize.y + GetScreenHeight()))
		{
			minY = ThePlayer->Y() - GetScreenHeight();
			maxY = FieldSize.y;
		}
		else if (ThePlayer->Y() > (FieldSize.y - GetScreenHeight()))
		{
			minY = ThePlayer->Y() - GetScreenHeight();
			maxY = -ThePlayer->Y() + GetScreenHeight();
		}
		else
		{
			if (GetRandomValue(1, 10) > 5)
			{
				minY = -FieldSize.y;
				maxY = FieldSize.y;
			}
			else
			{
				minY = -FieldSize.y;
				maxY = FieldSize.y;
			}
		}

		spawnPosition.x = GetRandomFloat(minX, maxX);
		spawnPosition.y = GetRandomFloat(minY, maxY);

		Ones[spawnNumber]->Spawn(spawnPosition);
	}
}
