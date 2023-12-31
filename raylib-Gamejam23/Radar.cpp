#include "Radar.h"

Radar::Radar()
{
}

Radar::~Radar()
{
}

bool Radar::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool Radar::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void Radar::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	SetRotationZFromVectors(Target);
}

void Radar::Draw()
{
	Model3D::Draw();

}

void Radar::SetTarget(Vector3& target)
{
	Target = target;
}

void Radar::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}