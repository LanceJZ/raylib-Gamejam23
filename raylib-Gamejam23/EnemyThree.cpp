#include "EnemyThree.h"

EnemyThree::EnemyThree()
{
}

EnemyThree::~EnemyThree()
{
}

void EnemyThree::SetBase(Base* base)
{
	TheBase = base;
}

bool EnemyThree::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	ThrustTimer = TheManagers.EM.AddTimer();
	ShotTimerTime = 1.5f;

	return true;
}

bool EnemyThree::BeginRun()
{
	Enemy::BeginRun();

	return false;
}

void EnemyThree::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	switch (InState)
	{
	case EnemyThree::EvadePlayer:
		Evade(deltaTime);
		break;
	case EnemyThree::WaitForTime:
		Wait(deltaTime);
		break;
	case EnemyThree::GoToBase:
		ReturnToBase(deltaTime);
		break;
	case EnemyThree::Patrol:
		Patrolling(deltaTime);
		break;
	case EnemyThree::AttackPlayer:
		Attack(deltaTime);
		break;
	default:
		break;
	}
}

void EnemyThree::Draw()
{
	Enemy::Draw();

}

void EnemyThree::Evade(float deltaTime)
{
}

void EnemyThree::Wait(float deltaTime)
{
}

void EnemyThree::ReturnToBase(float deltaTime)
{
}

void EnemyThree::Patrolling(float deltaTime)
{
	if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
	{
		Thrust = GetRandomFloat(10.0f, 30.0f);
		TheManagers.EM.Timers[ThrustTimer]->Reset(5.0f);
	}

	Vector3 heading = CheckOtherSide(Waypoints[WaypointNumber]);

	SetHeading(heading, 0.3666f);
	SetAccelerationToMaxAtRotation(Thrust, 0.05f, deltaTime);

	float distance = Vector3Distance(heading, Position);

	if (distance < 210)
	{
		if (WaypointNumber < 3) WaypointNumber++;
		else WaypointNumber = 0;
	}

	float playerDistance = Vector3Distance(heading, ThePlayer->Position);

	if (playerDistance < 300) InState = AIState::AttackPlayer;
}

void EnemyThree::Attack(float deltaTime)
{
	Vector3 heading = CheckOtherSide(Waypoints[WaypointNumber]);
	Vector3 playerAt = CheckOtherSide(ThePlayer->Position);
	float playerDistance = Vector3Distance(heading, ThePlayer->Position);

	if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
	{
		Thrust = GetRandomFloat(10.0f, 40.0f);
		TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
	}

	if (TheManagers.EM.Timers[ShotTimer]->Elapsed())
	{
		Fire();
		TheManagers.EM.Timers[ShotTimer]->Reset(3.15f);
	}

	SetHeading(playerAt, 0.4666f);
	SetAccelerationToMaxAtRotation(Thrust, 0.025f, deltaTime);

	if (playerDistance > 500) InState = AIState::Patrol;
}

void EnemyThree::Spawn(Vector3 position)
{
	Entity::Spawn(position);

	InState = AIState::Patrol;

	float dist = 150;

	Waypoints[0] = {TheBase->Position.x - dist,
		TheBase->Position.y + dist, 0}; //Top Left
	Waypoints[1] = {TheBase->Position.x + dist,
		TheBase->Position.y + dist, 0}; //Top Right
	Waypoints[2] = {TheBase->Position.x + dist,
		TheBase->Position.y - dist, 0}; //Bottom Right
	Waypoints[3] = {TheBase->Position.x - dist,
		TheBase->Position.y - dist, 0}; // Bottom Left
}