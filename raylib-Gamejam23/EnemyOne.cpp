#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
}

EnemyOne::~EnemyOne()
{
}

bool EnemyOne::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void EnemyOne::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void EnemyOne::Draw()
{
	Model3D::Draw();

}
