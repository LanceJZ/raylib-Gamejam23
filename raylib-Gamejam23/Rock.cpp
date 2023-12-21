#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
}

bool Rock::Initialize(Utilities* utilities)
{
	EnemyBase::Initialize(utilities);

	RotationVelocityX = GetRandomFloat(-0.5f, 0.5f);
	RotationVelocityY = GetRandomFloat(-0.25f, 0.25f);
	RotationVelocityZ = GetRandomFloat(-0.1f, 0.1f);

	Radius = 25.0f;

	return false;
}

bool Rock::BeginRun()
{
	EnemyBase::BeginRun();

	return false;
}

void Rock::Update(float deltaTime)
{
	EnemyBase::Update(deltaTime);

	if (CheckCollision())
	{
		Enabled = false;
		Hit = true;
	}
}

void Rock::Draw()
{
	EnemyBase::Draw();

}

void Rock::Spawn(Vector3 position)
{
	EnemyBase::Spawn(position);

	float speed = 30.0f;
	OreAmount = GetRandomValue(0, 5);

	Velocity = { GetRandomFloat(-speed, speed), GetRandomFloat(-speed, speed), 0.0f };
}

bool Rock::CheckCollision()
{
	bool hit = false;

	for (auto shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot) && shot->Enabled)
		{
			hit = true;
			shot->Enabled = false;
		}
	}

	return hit;
}

int Rock::GetAmountOfOre()
{
	return OreAmount;
}
