#include "GameLogic.h"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::SetPlayer(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

void GameLogic::SetEnemies(EnemyControl* enemies)
{
	Enemies = enemies;
}

void GameLogic::SetOreModel(Model& model)
{
	OreModel = model;
}

bool GameLogic::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

	AdjustedSize = Vector2Multiply(FieldSize, { 0.5f, 0.5f });

	return true;
}

bool GameLogic::BeginRun()
{
	RockSpawnTimer = TheManagers.EM.AddTimer();

	return true;
}

void GameLogic::Input()
{

}

void GameLogic::Update()
{
	CameraUpdate();
	PlayerOverEdge();
	CheckForOreToSpawn();
	CheckToSpawnRocks();
}

void GameLogic::SpawnOre(int amount, Vector3 position)
{
	for (int i = 0; i < amount; i++)
	{
		bool spawnNew = true;
		size_t spawnNumber = OreCollection.size();

		for (size_t check = 0; check < spawnNumber; check++)
		{
			if (!OreCollection[check]->Enabled)
			{
				spawnNew = false;
				spawnNumber = check;
				break;
			}
		}

		if (spawnNew)
		{
			//When adding as a new class, make sure to use DBG_NEW.
			OreCollection.push_back(DBG_NEW Ore());
			TheManagers.EM.AddModel3D(OreCollection[spawnNumber], OreModel);
			OreCollection[spawnNumber]->SetPlayer(ThePlayer);
			OreCollection[spawnNumber]->Initialize(TheUtilities);
			OreCollection[spawnNumber]->BeginRun();
		}

		OreCollection[spawnNumber]->Spawn(position);
	}

}

void GameLogic::PlayerOverEdge()
{
	if (ThePlayer->X() > AdjustedSize.x) ThePlayer->X(-AdjustedSize.x);
	if (ThePlayer->X() < -AdjustedSize.x) ThePlayer->X(AdjustedSize.x);
	if (ThePlayer->Y() > AdjustedSize.y) ThePlayer->Y(-AdjustedSize.y);
	if (ThePlayer->Y() < -AdjustedSize.y) ThePlayer->Y(AdjustedSize.y);
}

void GameLogic::CameraUpdate()
{
	TheCamera.position.x = ThePlayer->Position.x;
	TheCamera.position.y = ThePlayer->Position.y;
	TheCamera.target.x = TheCamera.position.x;
	TheCamera.target.y = TheCamera.position.y;
}

void GameLogic::CheckForOreToSpawn()
{
	for (auto rock : Enemies->Rocks)
	{
		if (rock == nullptr) return;

		if (rock->Hit && rock->Enabled)
		{
			rock->Disable();

			SpawnOre(rock->GetAmountOfOre(), rock->Position);
			RocksToSpawn++;
			TheManagers.EM.Timers[RockSpawnTimer]->Reset(3);

			for (auto enemyOne : Enemies->Ones)
			{
				enemyOne->SetOre(OreCollection);
			}
		}
	}
}

void GameLogic::CheckToSpawnRocks()
{
	if (RocksToSpawn > 0 && TheManagers.EM.Timers[RockSpawnTimer]->Elapsed())
	{
		Enemies->SpawnRocks(RocksToSpawn);
		RocksToSpawn = 0;
	}
}
