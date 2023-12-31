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

	ScreenTop = GetScreenHeight() * 0.85f;
	FieldAdjusted = FieldSize.y * 0.01;

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

	float distance = Vector3Distance(Position, Target);
	int alpha = 255;
	distance -= (ScreenTop + FieldAdjusted);

	if (distance < 0) distance = 1;

	alpha -= (int)Clamp(distance, 0, 150);

	ModelColor = {ArrowColor.r, ArrowColor.g, ArrowColor.b,
		(unsigned char)alpha};
}

void Radar::Draw()
{
	Model3D::Draw();

}

void Radar::SetTarget(Vector3& target)
{
	Target = target;
}

void Radar::SetColor(Color& color)
{
	ArrowColor = color;
}

void Radar::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}