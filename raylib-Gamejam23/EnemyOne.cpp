#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
}

EnemyOne::~EnemyOne()
{
}

bool EnemyOne::BeginRun()
{
	EnemyBase::BeginRun();

	return false;
}

void EnemyOne::Update(float deltaTime)
{
	EnemyBase::Update(deltaTime);

}

void EnemyOne::Draw()
{
	EnemyBase::Draw();

}
