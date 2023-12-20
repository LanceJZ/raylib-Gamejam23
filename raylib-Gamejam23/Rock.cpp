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

}

void Rock::Draw()
{
	EnemyBase::Draw();

}
