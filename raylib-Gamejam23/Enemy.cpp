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

void Enemy::SetArrowModel(Model& model)
{
	TheManagers.EM.AddModel3D(RadarArrow = DBG_NEW Radar(), model);
	Color red = RED;
	RadarArrow->SetColor(red);
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

	if (RadarArrow != nullptr)
	{
		RadarArrow->Position = ThePlayer->Position;
		RadarArrow->Enabled = Enabled;
		RadarArrow->SetTarget(Position);
	}
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

	Vector3 drift = { 0.01f, 0.01f, 0.01f };

	ShotNumber = shotNumber;

	float speed = 100.0f;

	Fire(Position, VelocityFromAngleZ(speed));
}

void Enemy::Fire(Vector3 position, Vector3 velocity)
{
	Shots[ShotNumber]->Spawn(position, Vector3Add(Velocity, velocity), ShotTimerTime);
}

Vector3 Enemy::CheckOtherSide(Vector3 target)
{
	Vector2 screenSize = { GetScreenWidth(), GetScreenHeight() };
	Vector2 otherSide = Vector2Subtract(FieldSize, screenSize);

	if (WorldPosition.x - target.x > otherSide.x ||
		target.x - WorldPosition.x > otherSide.x)
	{
		if (target.x < WorldPosition.x)
		{
			target.x += FieldSize.x;
		}
		else
		{
			target.x -= FieldSize.x;
		}
	}

	if (WorldPosition.y - target.y > otherSide.y ||
		target.y - WorldPosition.y > otherSide.y)
	{
		if (target.y < WorldPosition.y)
		{
			target.y += FieldSize.y;
		}
		else
		{
			target.y -= FieldSize.y;
		}
	}

	return target;
}
