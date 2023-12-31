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
	ShotTimerTime = 2.0f;

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
	case Evade:
		break;
	case SearchForDrone:
		Search();
		break;
	case GoToDrone:
		HeadToDrone(deltaTime);
		break;
	case Wait:
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

void EnemyTwo::Runaway(float deltaTime)
{
	float distance = Vector3Distance(Position, DroneProtecting->Position);
	float distanceFromPlayer = Vector3Distance(Position, ThePlayer->Position);
}

void EnemyTwo::Search()
{
	Acceleration = {};
	RotationAccelerationZ = {};
	DroneProtecting = FindDrone();
	InState = AIState::GoToDrone;
}

void EnemyTwo::HeadToDrone(float deltaTime)
{
	float distance = Vector3Distance(Position, DroneProtecting->Position);

	if (distance > 300.0f + DroneProtecting->Radius)
	{//Far away
		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			Thrust = GetRandomFloat(10.0f, 50.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(DroneProtecting->Position, 3.666f);
		SetAccelerationToMaxAtRotation(Thrust, 0.005f, deltaTime);
	}
	else
	{
		Acceleration = {};
		RotationAccelerationZ = {};
		InState = AIState::Patrol;

		float farX = 0;
		float farY = 0;

		if (DroneProtecting->Position.x > 0)
		{
			farX = DroneProtecting->Position.x + 150;

		}
		else
		{
			farX = DroneProtecting->Position.x - 150;
		}

		if (DroneProtecting->Position.y > 0)
		{

			farY = DroneProtecting->Position.y + 100;
		}
		else
		{
			farY = DroneProtecting->Position.y - 100;
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
	float distance = Vector3Distance(Position, DroneProtecting->Position);
	float distanceFromPlayer = Vector3Distance(Position, ThePlayer->Position);

	if (distance < 400)
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
	float distanceFromDrone = Vector3Distance(Position, DroneProtecting->Position);
	float distanceFromPlayer = Vector3Distance(Position, ThePlayer->Position);

	if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
	{
		Thrust = GetRandomFloat(10.0f, 40.0f);
		TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
	}

	if (TheManagers.EM.Timers[ShotTimer]->Elapsed())
	{
		Fire();
		TheManagers.EM.Timers[ShotTimer]->Reset(1.5f);
	}

	SetHeading(ThePlayer->Position, 1.666f);
	SetAccelerationToMaxAtRotation(Thrust, 0.01f, deltaTime);

	if (distanceFromDrone < distanceFromPlayer) InState = AIState::SearchForDrone;
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
			float droneDistance = Vector3Distance(drone->Position, Position);

			if (droneDistance < distance || distance < 0.0f)
			{
				distance = droneDistance;
				foundDrone = drone;
			}
		}
	}

	return foundDrone;
}
