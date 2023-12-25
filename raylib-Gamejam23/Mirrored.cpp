#include "Mirrored.h"

Mirrored::Mirrored()
{
}

Mirrored::~Mirrored()
{
}

bool Mirrored::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	AdjustedSize = Vector2Multiply(FieldSize, { 0.5f, 0.5f });

	return true;
}

bool Mirrored::BeginRun()
{
	Model3D::BeginRun();

	TheManagers.EM.AddModel3D(MirrorModelL = new Model3D());
	TheManagers.EM.AddModel3D(MirrorModelR = new Model3D());

	MirrorModelL->SetModel(GetModel());
	MirrorModelR->SetModel(GetModel());
	MirrorModelL->Cull = false;
	MirrorModelR->Cull = false;


	return true;
}

void Mirrored::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Position.x > AdjustedSize.x - (GetScreenWidth() * 0.5f))
	{
		MirrorModelL->Position.x = Position.x - FieldSize.x;
		MirrorModelL->Position.y = Position.y;
		MirrorModelL->RotationX = RotationX;
		MirrorModelL->RotationY = RotationY;
		MirrorModelL->RotationZ = RotationZ;
		MirrorModelL->Enabled = true;
	}
	else
	{
		MirrorModelL->Enabled = false;
	}

	if (Position.x < -AdjustedSize.x + (GetScreenWidth() * 0.5f))
	{
		MirrorModelR->Position.x = Position.x + FieldSize.x;
		MirrorModelR->Position.y = Position.y;
		MirrorModelR->RotationX = RotationX;
		MirrorModelR->RotationY = RotationY;
		MirrorModelR->RotationZ = RotationZ;
		MirrorModelR->Enabled = true;
	}
	else
	{
		MirrorModelR->Enabled = false;
	}


}

void Mirrored::Draw()
{
	Model3D::Draw();

}

void Mirrored::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}