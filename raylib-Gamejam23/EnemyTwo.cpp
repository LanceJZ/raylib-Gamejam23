#include "EnemyTwo.h"

EnemyTwo::EnemyTwo()
{
}

EnemyTwo::~EnemyTwo()
{
}

void EnemyTwo::SetOnes(std::vector<EnemyOne*> &ones)
{
	Ones = ones;
}

bool EnemyTwo::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	ThrustTimer = TheManagers.EM.AddTimer();
	ShotTimerTime = 2.75f;

	return false;
}

bool EnemyTwo::BeginRun()
{
	Enemy::BeginRun();

	return false;
}

void EnemyTwo::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	switch (InState)
	{
	case EvadePlayer:
		Evade(deltaTime);
		break;
	case SearchForDrone:
		Search(deltaTime);
		break;
	case GoToDrone:
		HeadToDrone(deltaTime);
		break;
	case WaitForTime:
		Wait(deltaTime);
		break;
	case Patrol:
		PatrolArea(deltaTime);
		break;
	case AttackPlayer:
		Attack(deltaTime);
		break;
	default:
		break;
	}
}

void EnemyTwo::Draw()
{
	Enemy::Draw();

}

void EnemyTwo::Spawn(Vector3 position)
{
	Enemy::Spawn(position);

	InState = AIState::SearchForDrone;
}

void EnemyTwo::Evade(float deltaTime)
{
}

void EnemyTwo::Runaway(float deltaTime)
{
	float distance = Vector3Distance(Position,
		CheckOtherSide(DroneProtecting->Position));
	float distanceFromPlayer = Vector3Distance(Position,
		CheckOtherSide(ThePlayer->Position));
}

void EnemyTwo::Search(float deltaTime)
{
	Acceleration = {};
	RotationAccelerationZ = {};
	DroneProtecting = FindDrone();
	InState = AIState::GoToDrone;
}

void EnemyTwo::Wait(float deltaTime)
{
}

void EnemyTwo::HeadToDrone(float deltaTime)
{
	Vector3 dronePosition = CheckOtherSide(DroneProtecting->Position);

	float distance = Vector3Distance(Position, dronePosition);

	if (distance > 300.0f + DroneProtecting->Radius)
	{//Far away
		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			Thrust = GetRandomFloat(10.0f, 50.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(dronePosition, 3.666f);
		SetAccelerationToMaxAtRotation(Thrust, 0.005f, deltaTime);
	}
	else
	{
		Acceleration = {};
		RotationAccelerationZ = {};
		InState = AIState::Patrol;

		float farX = 0;
		float farY = 0;

		if (dronePosition.x > 0)
		{
			farX = dronePosition.x + 150;

		}
		else
		{
			farX = dronePosition.x - 150;
		}

		if (dronePosition.y > 0)
		{

			farY = dronePosition.y + 100;
		}
		else
		{
			farY = dronePosition.y - 100;
		}

		Waypoints[0] = {-farX, farY, 0}; //Top Left
		Waypoints[1] = {farX, farY, 0}; //Top Right
		Waypoints[2] = {farX, -farY, 0}; //Bottom Right
		Waypoints[3] = {-farX, -farY, 0}; // Bottom Left
	}

	if (!DroneProtecting->Enabled) InState = AIState::SearchForDrone;
}

void EnemyTwo::PatrolArea(float deltaTime)
{

	Vector3 dronePosition = CheckOtherSide(DroneProtecting->Position);

	float distance = Vector3Distance(Position,
		dronePosition);
	float distanceFromPlayer = Vector3Distance(Position,
		CheckOtherSide(ThePlayer->Position));

	if (800 > distance)
	{
		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			Thrust = GetRandomFloat(10.0f, 30.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(5.0f);
		}

		SetHeading(Waypoints[WaypointNumber], 0.666f);
		SetAccelerationToMaxAtRotation(Thrust, 0.015f, deltaTime);

		if (Vector3Distance(Waypoints[WaypointNumber], Position) < 40)
		{
			if (WaypointNumber < 3) WaypointNumber++;
			else WaypointNumber = 0;
		}
	}
	else
	{
		InState = AIState::GoToDrone;
	}

	if (!DroneProtecting->Enabled)
	{
		InState = AIState::SearchForDrone;
		return;
	}

	if (distance > distanceFromPlayer) InState = AIState::AttackPlayer;
}

void EnemyTwo::Attack(float deltaTime)
{
	Vector3 playerAt = CheckOtherSide(ThePlayer->Position);

	float distanceFromPlayer = Vector3Distance(Position, playerAt);

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

	SetHeading(playerAt, 1.666f);
	SetAccelerationToMaxAtRotation(Thrust, 0.01f, deltaTime);

	if (distanceFromPlayer > 800) InState = AIState::SearchForDrone;
}

EnemyOne* EnemyTwo::FindDrone()
{
	float distance = -1.0f;
	Velocity = {};
	Acceleration = {};
	EnemyOne* foundDrone = nullptr;

	for (auto drone : Ones)
	{
		if (drone->Enabled)
		{
			float droneDistance = Vector3Distance(CheckOtherSide(drone->Position),
				Position);

			if (droneDistance < distance || distance < 0.0f)
			{
				distance = droneDistance;
				foundDrone = drone;
			}
		}
	}

	return foundDrone;
}
