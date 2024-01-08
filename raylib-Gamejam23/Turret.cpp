#include "Turret.h"

Turret::Turret()
{
}

Turret::~Turret()
{
}

bool Turret::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	ShotTimerTime = GetRandomFloat(2.0f, 3.0f);

	return false;
}

bool Turret::BeginRun()
{
	Enemy::BeginRun();

	return false;
}

void Turret::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	//if (WasCulled) return;

	FireAtPlayer();
}

void Turret::Draw()
{
	Enemy::Draw();

}

void Turret::FireAtPlayer()
{
	float speed = 150.0f;

	BeforeCalculate();
	CalculateWorldVectors();
	CalculateWorldSpace();
	AfterCalculate();

	if (Vector3Distance(WorldPosition, ThePlayer->Position) < 1000 && Enabled)
	{
		if (TheManagers.EM.Timers[ShotTimer]->Elapsed())
		{
			Fire(GetVelocityFromAngleZ(WorldRotation.z, speed));
			ShotTimerTime = GetRandomFloat(2.0f, 5.0f);
		}
	}

}

void Turret::Fire(Vector3 velocity)
{
	Enemy::Fire();
	Enemy::Fire(WorldPosition, velocity);
}
