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
			GoToRock();
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
	if (rockToMine == nullptr)
	{
		rockToMine = FindCloseRock();
		InState = AIState::GoToRock;
	}
}

Rock* EnemyOne::FindCloseRock()
{
	Vector3 rockPosition;
	rockToMine = nullptr;
	float distance = -1;

	for (auto rock : Rocks)
	{
		float rockDistance = Vector3Distance(rock->Position, Position);

		if (rockDistance < distance || rockDistance < 0.0f)
		{
			distance = rockDistance;
			rockToMine = rock;
		}
	}

	return rockToMine;
}

void EnemyOne::GoToRock()
{
}
