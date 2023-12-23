#include "GameLogic.h"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::SetCamera(Camera* cam)
{
	Cam = cam;
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

	return false;
}

bool GameLogic::BeginRun()
{

	return false;
}

void GameLogic::Input()
{

}

void GameLogic::Update()
{
	CameraUpdate();
	PlayerOverEdge();
	CheckForOreToSpawn();
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
	if (ThePlayer->X() > FieldSize.x * 0.5f) ThePlayer->X(-FieldSize.x * 0.5f);
	if (ThePlayer->X() < -FieldSize.x * 0.5f) ThePlayer->X(FieldSize.x * 0.5f);
	if (ThePlayer->Y() > FieldSize.y * 0.5f) ThePlayer->Y(-FieldSize.y * 0.5f);
	if (ThePlayer->Y() < -FieldSize.y * 0.5f) ThePlayer->Y(FieldSize.y * 0.5f);
}

void GameLogic::CameraUpdate()
{
	Cam->position.x = ThePlayer->Position.x;
	Cam->position.y = ThePlayer->Position.y;
	Cam->target.x = Cam->position.x;
	Cam->target.y = Cam->position.y;
}

void GameLogic::CheckForOreToSpawn()
{
	for (auto rock : Enemies->Rocks)
	{
		if (rock == nullptr) return;

		if (rock->Hit && rock->Enabled)
		{
			rock->Hit = false;
			rock->Enabled = false;
			SpawnOre(rock->GetAmountOfOre(), rock->Position);
			//SpawnOre(1, rock->Position);
			Enemies->SpawnRocks(1);

			for (auto enemyOne : Enemies->Ones)
			{
				enemyOne->SetOre(OreCollection);
			}
		}
	}
}
