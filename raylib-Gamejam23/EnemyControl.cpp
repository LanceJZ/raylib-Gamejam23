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

void EnemyControl::SetEnemyBaseModel(Model& model)
{
	EnemyBaseModel = model;
}

void EnemyControl::SetEnemyBaseTurretModel(Model& model)
{
	EnemyBaseTurretModel = model;
}

void EnemyControl::SetShotModel(Model& model)
{
	ShotModel = model;
}

void EnemyControl::SetEnemyOneModel(Model& model)
{
	EnemyOneModel = model;
}

void EnemyControl::SetEnemyTwoModel(Model& model)
{
	EnemyTwoModel = model;
}

void EnemyControl::SetEnemyThreeModel(Model& model)
{
	EnemyThreeModel = model;
}

void EnemyControl::SetRockModel(Model& model)
{
	RockModel = model;
}

void EnemyControl::SetArrowModel(Model& model)
{
	ArrowModel = model;
}

bool EnemyControl::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	return false;
}

bool EnemyControl::BeginRun()
{
	EnemyBase = new Base();
	TheManagers.EM.AddModel3D(EnemyBase, EnemyBaseModel);
	EnemyBase->SetTurretModel(EnemyBaseTurretModel);
	EnemyBase->SetArrowModel(ArrowModel);
	EnemyBase->SetShotModel(ShotModel);
	EnemyBase->SetPlayer(ThePlayer);
	EnemyBase->Initialize(TheUtilities);
	EnemyBase->BeginRun();

	Reset();

	return false;
}

void EnemyControl::Update()
{
	Common::Update();

}

void EnemyControl::Reset()
{
	SpawnEnemyBase();
	SpawnRocks(20);
	SpawnEnemyOne(10);
	SpawnEnemyTwo(5);
	SpawnEnemyThree(1);
}

void EnemyControl::SpawnEnemyBase()
{
	EnemyBase->Spawn(PositionAwayFromPlayer());
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
			TheManagers.EM.AddModel3D(Ones[spawnNumber], EnemyOneModel);
			Ones[spawnNumber]->SetPlayer(ThePlayer);
			Ones[spawnNumber]->SetBase(EnemyBase);
			Ones[spawnNumber]->SetRocks(Rocks);
			Ones[spawnNumber]->SetShotModel(ShotModel);
			Ones[spawnNumber]->SetArrowModel(ArrowModel);
			Ones[spawnNumber]->Initialize(TheUtilities);
			Ones[spawnNumber]->BeginRun();
		}

		Ones[spawnNumber]->Spawn(PositionAwayFromPlayer());
	}
}

void EnemyControl::SpawnEnemyTwo(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = Twos.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!Twos[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			//When adding as a new class, make sure to use DBG_NEW.
			Twos.push_back(DBG_NEW EnemyTwo());
			TheManagers.EM.AddModel3D(Twos[spawnNumber], EnemyTwoModel);
			Twos[spawnNumber]->SetPlayer(ThePlayer);
			Twos[spawnNumber]->SetShotModel(ShotModel);
			Twos[spawnNumber]->SetArrowModel(ArrowModel);
			Twos[spawnNumber]->SetOnes(Ones);
			Twos[spawnNumber]->Initialize(TheUtilities);
			Twos[spawnNumber]->BeginRun();
		}

		Twos[spawnNumber]->Spawn(PositionAwayFromPlayer());
	}
}

void EnemyControl::SpawnEnemyThree(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = Threes.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!Threes[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			//When adding as a new class, make sure to use DBG_NEW.
			Threes.push_back(DBG_NEW EnemyThree());
			TheManagers.EM.AddModel3D(Threes[spawnNumber], EnemyThreeModel);
			Threes[spawnNumber]->SetPlayer(ThePlayer);
			Threes[spawnNumber]->SetShotModel(ShotModel);
			Threes[spawnNumber]->SetArrowModel(ArrowModel);
			Threes[spawnNumber]->SetBase(EnemyBase);
			Threes[spawnNumber]->Initialize(TheUtilities);
			Threes[spawnNumber]->BeginRun();
		}

		Threes[spawnNumber]->Spawn(EnemyBase->Position);
	}
}

void EnemyControl::SpawnRocks(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = Rocks.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!Rocks[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			//When adding as a new class, make sure to use DBG_NEW.
			Rocks.push_back(DBG_NEW Rock());
			TheManagers.EM.AddModel3D(Rocks[spawnNumber], RockModel);
			Rocks[spawnNumber]->SetPlayer(ThePlayer);
			Rocks[spawnNumber]->Initialize(TheUtilities);
			Rocks[spawnNumber]->BeginRun();
		}

		Rocks[spawnNumber]->Spawn(PositionAwayFromPlayer());
	}

}

Vector3 EnemyControl::PositionAwayFromPlayer()
{
		Vector3 spawnPosition = {};
		float minX = 0.0f;
		float maxX = 0.0f;
		float minY = 0.0f;
		float maxY = 0.0f;
		float sw = GetScreenWidth() * 0.5f;
		float sh = GetScreenHeight() * 0.5f;

		int sx = GetRandomValue(1, 10);
		int sy = GetRandomValue(1, 10);

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


	return spawnPosition;
}
