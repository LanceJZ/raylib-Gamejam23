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
		float sw = GetScreenWidth() * 0.5f;
		float sh = GetScreenHeight() * 0.5f;

		float sx = GetRandomValue(1, 10);
		float sy = GetRandomValue(1, 10);

		Vector2 fs = {};
		fs.x = FieldSize.x * 0.5f;
		fs.y = FieldSize.y * 0.5f;

		if (ThePlayer->X() < (-fs.x + sw))
		{
			minX = ThePlayer->X() + sw;
			maxX = fs.x;
		}
		else if (ThePlayer->X() > (fs.x - sw))
		{
			minX = -fs.x;
			maxX = ThePlayer->X() - sw;
		}
		else
		{
			if (sx > 5)
			{
				minX = -fs.x;
				maxX = ThePlayer->X() - sw;
			}
			else
			{
				minX = ThePlayer->X() + sw;
				maxX = fs.x;
			}
		}

		if (ThePlayer->Y() < (-fs.y + sh))
		{
			minY = ThePlayer->Y() + sh;
			maxY = fs.y;
		}
		else if (ThePlayer->Y() > (fs.y - sh))
		{
			minY = -fs.y;
			maxY = ThePlayer->Y() - sh;
		}
		else
		{
			if (sy > 5)
			{
				minY = -fs.y;
				maxY = ThePlayer->Y() - sh;
			}
			else
			{
				minY = ThePlayer->Y() + sh;
				maxY = fs.y;
			}
		}

		spawnPosition.x = GetRandomFloat(minX, maxX);
		spawnPosition.y = GetRandomFloat(minY, maxY);

		Ones[spawnNumber]->Spawn(spawnPosition);
	}
}
