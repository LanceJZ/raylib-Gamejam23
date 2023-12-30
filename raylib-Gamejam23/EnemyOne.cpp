#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
}

EnemyOne::~EnemyOne()
{
}

void EnemyOne::SetBase(Base* base)
{
	EnemyBase = base;
}

void EnemyOne::SetRocks(std::vector<Rock*> &rocks)
{
	Rocks = rocks;
}

void EnemyOne::SetOre(std::vector<Ore*> &ore)
{
	OreCollection = ore;
}

bool EnemyOne::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	Radius = 9.5f;
	MaxSpeed = 0.00004f;
	ShotTimerTime = 6.666f;
	InState = AIState::FindRock;

	ThrustTimer = TheManagers.EM.AddTimer();

	return false;
}

bool EnemyOne::BeginRun()
{
	Enemy::BeginRun();


	return false;
}

void EnemyOne::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	switch (InState)
	{
		case AIState::FindRock:
			Search();
			break;

		case AIState::GoToRock:
			HeadToRock(deltaTime);
			break;

		case AIState::RetrieveOre:
			HeadToOre(deltaTime);
			break;

		case AIState::ReturnToBase:
			HeadToBase(deltaTime);
			break;

		case AIState::Mine:
			MineRock();
			break;

		default:
			break;
	}
}

void EnemyOne::Draw()
{
	Enemy::Draw();

}

void EnemyOne::Search()
{
	Acceleration = {};
	RockToMine = GetNearbyRock();
	InState = AIState::GoToRock;
}

Rock* EnemyOne::GetNearbyRock()
{
	float distance = -1.0f;
	Velocity = {};
	Acceleration = {};
	Rock* foundRock = nullptr;

	for (auto rock : Rocks)
	{
		if (rock->Enabled)
		{
			float rockDistance = Vector3Distance(rock->Position, Position);

			if (rockDistance < distance || distance < 0.0f)
			{
				distance = rockDistance;
				foundRock = rock;
			}
		}
	}

	return foundRock;
}

Ore* EnemyOne::FindCloseOre()
{
	float distance = -1.0f;
	Ore* foundOre = nullptr;

	for (auto ore : OreCollection)
	{
		if (ore->Enabled && !ore->Grabbed)
		{
			float rockDistance = Vector3Distance(ore->Position, Position);

			if (rockDistance < distance || distance < 0.0f)
			{
				distance = rockDistance;
				foundOre = ore;
			}
		}
	}

	return foundOre;
}

void EnemyOne::HeadToRock(float deltaTime)
{
	if (RockToMine == nullptr)
	{
		InState = AIState::FindRock;
		return;
	}

	if (!RockToMine->Enabled)
	{
		InState = AIState::FindRock;
		return;
	}

	float distance = Vector3Distance(RockToMine->Position, Position);

	if (distance < 30 + RockToMine->Radius)
	{
		InState = AIState::Mine;
		TheManagers.EM.Timers[ShotTimer]->Reset(10.0f);
		return;
	}

	if (distance < 150.0f + RockToMine->Radius)
	{//Closer
		MaxVelocity = 3.0f;

		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			Thrust = GetRandomFloat(10.0f, 30.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(RockToMine->Position, 3.666f);
		SetAccelerationToMaxAtRotation(Thrust, 0.02f, deltaTime);
	}
	else
	{//Further
		MaxVelocity = 50.0f;

		if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
		{
			Thrust = GetRandomFloat(20.0f, 50.0f);
			TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
		}

		SetHeading(RockToMine->Position, 1.666f);
		SetAccelerationToMaxAtRotation(Thrust, 0.015f, deltaTime);
	}

	CheckForOre();
}

void EnemyOne::HeadToOre(float deltaTime)
{
	if (OreToGrab == nullptr)
	{
		InState = AIState::FindRock;
		return;
	}

	if (!OreToGrab->Enabled || OreToGrab->Grabbed)
	{
		InState = AIState::FindRock;
		return;
	}

	float distance = Vector3Distance(OreToGrab->Position, Position);

	if (distance > 1000)
	{
		InState = AIState::FindRock;
		return;
	}

	MaxVelocity = 30.0f;
	SetHeading(OreToGrab->Position, 3.666f);

	if (TheManagers.EM.Timers[ThrustTimer]->Elapsed())
	{
		Thrust = GetRandomFloat(10.0f, 30.0f);
		TheManagers.EM.Timers[ThrustTimer]->Reset(3.0f);
	}

	SetAccelerationToMaxAtRotation(Thrust, 0.015f, deltaTime);

	if (CirclesIntersect(*OreToGrab) && !OreToGrab->Grabbed)
	{
		OreToGrab->Grabbed = true;
		SetHeading(OreToGrab->Position, 4.666f);
		Velocity = {};
		Acceleration = {};
		RotationVelocityZ = 0;
		OreInGraspPosition = Vector3Subtract(OreToGrab->Position, Position);
		InState = AIState::ReturnToBase;
	}
}

void EnemyOne::HeadToBase(float deltaTime)
{
	SetHeading(EnemyBase->Position, 1.666f);
	SetAccelerationToMaxAtRotation(1, 0.01f, deltaTime);

	OreToGrab->Position = Vector3Add(Position, OreInGraspPosition);

	if (OreToGrab->CirclesIntersect(*EnemyBase))
	{
		EnemyBase->DropOffOre();
		Reset();
	}
}

void EnemyOne::MineRock()
{
	if (RockToMine == nullptr || RockToMine->Enabled == false)
	{
		InState = AIState::FindRock;
		return;
	}

	Velocity = RockToMine->Velocity;
	Acceleration = {};
	SetHeading(RockToMine->Position, 4.666f);

	//if (Vector3Distance(RockToMine->Position, Position) > 40 + RockToMine->Radius)
	//{
	//	InState = AIState::FindRock;
	//	return;
	//}

	if (TheManagers.EM.Timers[ShotTimer]->Elapsed())
	{
		Fire();
	}

	CheckMining();
	CheckForOre();
}

bool EnemyOne::CheckCollusion()
{
	return false;
}

bool EnemyOne::CheckMining()
{
	for (auto shot : Shots)
	{
		for (auto rock : Rocks)
		{
			if (shot->CirclesIntersect(*rock) && rock->Enabled && shot->Enabled)
			{
				shot->Disable();

				rock->Hardness -= 10;

				if (rock->Hardness <= 0)
				{
					rock->Hit = true;
				}
			}
		}
	}

	return false;
}

bool EnemyOne::CheckForOre()
{

	OreToGrab = FindCloseOre();

	if (OreToGrab == nullptr) return false;

	float distance = Vector3Distance(OreToGrab->Position, Position);

	if (!OreToGrab->Grabbed && distance < 800.0f)
	{
		InState = AIState::RetrieveOre;
		return true;
	}

	return false;
}

void EnemyOne::Reset()
{
	InState = AIState::FindRock;
	Velocity = {};
	Acceleration = {};
	RotationVelocityZ = 0;

	if (OreToGrab != nullptr)
	{
		OreToGrab->Enabled = false;
		OreToGrab->Grabbed = false;
		OreToGrab->Disable();
		OreToGrab = nullptr;
	}
}
