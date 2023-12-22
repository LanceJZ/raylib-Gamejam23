#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
}

EnemyOne::~EnemyOne()
{
}

void EnemyOne::SetRocks(std::vector<Rock*> rocks)
{
	Rocks = rocks;
}

bool EnemyOne::Initialize(Utilities* utilities)
{
	EnemyBase::Initialize(utilities);

	MaxSpeed = 0.00004f;
	ShotTimerTime = 6.666f;
	InState = AIState::FindRock;

	return false;
}

bool EnemyOne::BeginRun()
{
	EnemyBase::BeginRun();


	return false;
}

void EnemyOne::Update(float deltaTime)
{
	EnemyBase::Update(deltaTime);

	switch (InState)
	{
		case AIState::FindRock:
			Search();
			break;
		case AIState::GoToRock:
			HeadToRock(deltaTime);
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
	EnemyBase::Draw();

}

void EnemyOne::Search()
{
	Velocity = {};
	Acceleration = {};
	RotationVelocity = 0;
	RockToMine = FindCloseRock();
	InState = AIState::GoToRock;
}

Rock* EnemyOne::FindCloseRock()
{
	float distance = -1.0f;
	Velocity = {};
	Acceleration = {};
	RotationVelocity = 0;


	for (auto rock : Rocks)
	{
		if (rock->Enabled)
		{
			float rockDistance = Vector3Distance(rock->Position, Position);

			if (rockDistance < distance || distance < 0.0f)
			{
				distance = rockDistance;
				RockToMine = rock;
			}
		}
	}

	return RockToMine;
}

void EnemyOne::HeadToRock(float deltaTime)
{
	if (RockToMine == nullptr || RockToMine->Enabled == false)
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
	else if (distance > 1000.0f)
	{
		InState = AIState::FindRock;
		return;
	}

	if (distance < 150.0f + RockToMine->Radius)
	{
		MaxVelocity = 3.0f;
		SetHeading(RockToMine->Position, 3.666f);
		SetAccelerationToMaxAtRotation(300.0f, 0.0015f, deltaTime);
	}
	else
	{
		MaxVelocity = 50.0f;
		SetHeading(RockToMine->Position, 2.666f);
		SetAccelerationToMaxAtRotation(200.0f, 0.00015f, deltaTime);
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

	if (Vector3Distance(RockToMine->Position, Position) > 40 + RockToMine->Radius)
	{
		InState = AIState::FindRock;
		return;
	}

	if (TheManagers.EM.Timers[ShotTimer]->Elapsed())
	{
		Fire();
	}

	CheckMining();
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
				shot->Enabled = false;
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
