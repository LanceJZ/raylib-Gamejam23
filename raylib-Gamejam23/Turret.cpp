#include "Turret.h"

Turret::Turret()
{
}

Turret::~Turret()
{
}

bool Turret::Initialize(Utilities* utilities)
{
	EnemyBase::Initialize(utilities);

	return false;
}

bool Turret::BeginRun()
{
	EnemyBase::BeginRun();

	return false;
}

void Turret::Update(float deltaTime)
{
	EnemyBase::Update(deltaTime);
	PointAtPlayer();
}

void Turret::Draw()
{
	EnemyBase::Draw();

}

void Turret::PointAtPlayer()
{
	//RotateTowardsTargetZ(ThePlayer->Position, 1.5f);
}
