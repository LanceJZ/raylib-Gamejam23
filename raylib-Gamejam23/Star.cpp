#include "Star.h"

Star::Star()
{
}

Star::~Star()
{
}

bool Star::Initialize(Utilities* utilities)
{
	Mirrored::Initialize(utilities);

	return false;
}

bool Star::BeginRun()
{
	Mirrored::BeginRun();

	return false;
}

void Star::Update(float deltaTime)
{
	Mirrored::Update(deltaTime);

}

void Star::Draw()
{
	Mirrored::Draw();

}

void Star::Spawn(Vector3 position)
{
	Mirrored::Spawn(position);

}