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
}
