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

bool EnemyOne::BeginRun()
{
	EnemyBase::BeginRun();

	MaxSpeed = 0.00004f;
	InState = AIState::FindRock;

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

	if (Vector3Distance(RockToMine->Position, Position) < 30 + RockToMine->Radius)
	{
		InState = AIState::Mine;
		return;
	}
	else if (Vector3Distance(RockToMine->Position, Position) > 1000.0f)
	{
		InState = AIState::FindRock;
		return;
	}


	if (Vector3Distance(RockToMine->Position, Position) < 150.0f + RockToMine->Radius)
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


	Vector3 accel = Acceleration;
	Vector3 vel = Velocity;
	float rotv = RotationVelocity;
	float rot = Rotation;
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
		InState = AIState::GoToRock;
	}
}
