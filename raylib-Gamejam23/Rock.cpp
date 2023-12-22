#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
}

void Rock::SetPlayer(Player* player)
{
	ThePlayer = player;
}

bool Rock::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	RotationVelocityX = GetRandomFloat(-0.5f, 0.5f);
	RotationVelocityY = GetRandomFloat(-0.25f, 0.25f);
	RotationVelocityZ = GetRandomFloat(-0.1f, 0.1f);

	Radius = 25.0f;

	return false;
}

bool Rock::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void Rock::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (X() > FieldSize.x * 0.5f) X(-FieldSize.x * 0.5f);
	if (X() < -FieldSize.x * 0.5f) X(FieldSize.x * 0.5f);
	if (Y() > FieldSize.y * 0.5f) Y(-FieldSize.y * 0.5f);
	if (Y() < -FieldSize.y * 0.5f) Y(FieldSize.y * 0.5f);

	if (Hit = CheckCollision())
	{
	}
}

void Rock::Draw()
{
	Model3D::Draw();

}

void Rock::Spawn(Vector3 position)
{
	Position = position;
	Enabled = true;

	Hardness = 100;
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
			shot->Enabled = false;

			Hardness -= 50;

			if (Hardness <= 0)
			{
				hit = true;
			}
		}
	}

	return hit;
}

int Rock::GetAmountOfOre() const
{
	return OreAmount;
}
