#include "Turret.h"

Turret::Turret()
{
}

Turret::~Turret()
{
}

bool Turret::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	return false;
}

bool Turret::BeginRun()
{
	Enemy::BeginRun();

	return false;
}

void Turret::Update(float deltaTime)
{
	Enemy::Update(deltaTime);
	PointAtPlayer();
}

void Turret::Draw()
{
	Enemy::Draw();

}

void Turret::PointAtPlayer()
{
	//RotateTowardsTargetZ(ThePlayer->Position, 1.5f);
}
