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
	float thrust = 10;

	if (distance > 300.0f + DroneProtecting->Radius)
	{//Closer
		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			thrust = GetRandomFloat(10.0f, 30.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(DroneProtecting->Position, 3.666f);
		SetAccelerationToMaxAtRotation(thrust, 0.01f, deltaTime);
	}
	else
	{
		Acceleration = {};
		RotationAccelerationZ = {};
		InState = AIState::Patrol;

		float farX = DroneProtecting->Position.x + 250;
		float farY = DroneProtecting->Position.x + 200;

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
	float thrust = 10;

	if (distance < 300)
	{
		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			thrust = GetRandomFloat(10.0f, 30.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(Waypoints[WaypointNumber], 0.666f);
		SetAccelerationToMaxAtRotation(thrust, 0.03f, deltaTime);

		if (Vector3Distance(Waypoints[WaypointNumber], Position) < 10)
		{
			if (WaypointNumber < 3) WaypointNumber++;
			else WaypointNumber = 0;
		}
	}
	else
	{
		InState = AIState::GoToDrone;
	}

	if (!DroneProtecting->Enabled) InState = AIState::SearchForDrone;
}

void EnemyTwo::Attack(float deltaTime)
{
	float distanceFromDrone = Vector3Distance(Position, DroneProtecting->Position);
	float distanceFromPlayer = Vector3Distance(Position, ThePlayer->Position);
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
