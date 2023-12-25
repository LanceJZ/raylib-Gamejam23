#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void Enemy::SetShotModel(Model &shotModel)
{
	ShotModel = shotModel;
}

bool Enemy::Initialize(Utilities* utilities)
{
	Mirrored::Initialize(utilities);

	ShotTimer = TheManagers.EM.AddTimer();

	return false;
}

bool Enemy::BeginRun()
{
	Mirrored::BeginRun();

	return false;
}

void Enemy::Update(float deltaTime)
{
	Mirrored::Update(deltaTime);

	if (X() > FieldSize.x * 0.5f) X(-FieldSize.x * 0.5f);
	if (X() < -FieldSize.x * 0.5f) X(FieldSize.x * 0.5f);
	if (Y() > FieldSize.y * 0.5f) Y(-FieldSize.y * 0.5f);
	if (Y() < -FieldSize.y * 0.5f) Y(FieldSize.y * 0.5f);
}

void Enemy::Draw()
{
	Mirrored::Draw();

}

void Enemy::Spawn(Vector3 position)
{
	Mirrored::Spawn(position);
}

void Enemy::Fire()
{
	TheManagers.EM.Timers[ShotTimer]->Reset(5.0f);
	bool spawnNewShot = true;
	size_t shotNumber = Shots.size();

	for (size_t shotCheck = 0; shotCheck < shotNumber; shotCheck++)
	{
		if (!Shots[shotCheck]->Enabled)
		{
			spawnNewShot = false;
			shotNumber = shotCheck;
			break;
		}
	}

	if (spawnNewShot)
	{
		//When adding as a new class, make sure to use DBG_NEW.
		Shots.push_back(DBG_NEW ShotMaster());
		TheManagers.EM.AddModel3D(Shots[shotNumber]);
		Shots[shotNumber]->SetModel(ShotModel, 2.5f);
		Shots[shotNumber]->Initialize(TheUtilities);
		Shots[shotNumber]->BeginRun();
	}

	float speed = 100.0f;
	Vector3 drift = { 0.01f, 0.01f, 0.01f };

	Shots[shotNumber]->Spawn(Position,
		Vector3Add(Velocity, VelocityFromAngleZ(speed)), ShotTimerTime);
}
