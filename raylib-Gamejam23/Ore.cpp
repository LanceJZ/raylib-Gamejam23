#include "Ore.h"

Ore::Ore()
{
}

Ore::~Ore()
{
}

void Ore::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool Ore::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	RotationVelocityX = GetRandomFloat(-0.5f, 0.5f);
	RotationVelocityY = GetRandomFloat(-0.25f, 0.25f);
	RotationVelocityZ = GetRandomFloat(-0.1f, 0.1f);

	Radius = 5.5f;

	return false;
}

bool Ore::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void Ore::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Ore::Draw()
{
	Model3D::Draw();

}

void Ore::Spawn(Vector3 position)
{
	Position = position;
	Enabled = true;

	Position.x += GetRandomFloat(-50.0f, 50.0f);
	Position.y += GetRandomFloat(-50.0f, 50.0f);

	Type = GetRandomValue(1, 4);
}

int Ore::GetOreType() const
{
	return Type;
}

bool Ore::CheckCollision()
{
	return false;
}
