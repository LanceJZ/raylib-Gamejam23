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
	TheManagers.EM.AddModel3D(MirrorModelT = new Model3D());
	TheManagers.EM.AddModel3D(MirrorModelB = new Model3D());
	//TheManagers.EM.AddModel3D(MirrorModelTR = new Model3D());
	//TheManagers.EM.AddModel3D(MirrorModelBR = new Model3D());
	//TheManagers.EM.AddModel3D(MirrorModelTL = new Model3D());
	//TheManagers.EM.AddModel3D(MirrorModelBL = new Model3D());

	MirrorModelL->SetModel(GetModel());
	MirrorModelR->SetModel(GetModel());
	MirrorModelT->SetModel(GetModel());
	MirrorModelB->SetModel(GetModel());
	//MirrorModelTL->SetModel(GetModel());
	//MirrorModelTR->SetModel(GetModel());
	//MirrorModelBL->SetModel(GetModel());
	//MirrorModelBR->SetModel(GetModel());

	return true;
}

void Mirrored::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (IsChild)
		return;

	if (X() > FieldSize.x * 0.5f) X(-FieldSize.x * 0.5f);
	if (X() < -FieldSize.x * 0.5f) X(FieldSize.x * 0.5f);
	if (Y() > FieldSize.y * 0.5f) Y(-FieldSize.y * 0.5f);
	if (Y() < -FieldSize.y * 0.5f) Y(FieldSize.y * 0.5f);

	if (Position.x > AdjustedSize.x - (GetScreenWidth() * 0.5f))
	{
		MirrorModelL->Position.x = Position.x - FieldSize.x;
		MirrorModelL->Position.y = Position.y;
		MirrorModelL->RotationX = RotationX;
		MirrorModelL->RotationY = RotationY;
		MirrorModelL->RotationZ = RotationZ;
		MirrorModelL->ModelColor = ModelColor;
		MirrorModelL->ModelScale = ModelScale;
		MirrorModelL->Enabled = Enabled;

		if (IsParent)
		{
			for (auto child : MirrorModelL->Children)
			{
				child->Enabled = MirrorModelL->Enabled;
			}
		}
	}
	else
	{
		MirrorModelL->Enabled = false;

		if (IsParent)
		{
			for (auto child : MirrorModelL->Children)
			{
				child->Enabled = MirrorModelL->Enabled;
			}
		}
	}

	if (Position.x < -AdjustedSize.x + (GetScreenWidth() * 0.5f))
	{
		MirrorModelR->Position.x = Position.x + FieldSize.x;
		MirrorModelR->Position.y = Position.y;
		MirrorModelR->RotationX = RotationX;
		MirrorModelR->RotationY = RotationY;
		MirrorModelR->RotationZ = RotationZ;
		MirrorModelR->ModelColor = ModelColor;
		MirrorModelR->ModelScale = ModelScale;
		MirrorModelR->Enabled = Enabled;

		if (IsParent)
		{
			for (auto child : MirrorModelR->Children)
			{
				child->Enabled = MirrorModelR->Enabled;
			}
		}
	}
	else
	{
		MirrorModelR->Enabled = false;

		if (IsParent)
		{
			for (auto child : MirrorModelR->Children)
			{
				child->Enabled = MirrorModelR->Enabled;
			}
		}
	}


	if (Position.y > AdjustedSize.y - (GetScreenHeight() * 0.5f))
	{
		MirrorModelT->Position.x = Position.x;
		MirrorModelT->Position.y = Position.y - FieldSize.y;
		MirrorModelT->RotationX = RotationX;
		MirrorModelT->RotationY = RotationY;
		MirrorModelT->RotationZ = RotationZ;
		MirrorModelT->ModelColor = ModelColor;
		MirrorModelT->ModelScale = ModelScale;
		MirrorModelT->Enabled = Enabled;

		if (IsParent)
		{
			for (auto child : MirrorModelT->Children)
			{
				child->Enabled = MirrorModelT->Enabled;
			}
		}
	}
	else
	{
		MirrorModelT->Enabled = false;

		if (IsParent)
		{
			for (auto child : MirrorModelT->Children)
			{
				child->Enabled = MirrorModelT->Enabled;
			}
		}
	}

	if (Position.y < -AdjustedSize.y + (GetScreenHeight() * 0.5f))
	{
		MirrorModelB->Position.x = Position.x;
		MirrorModelB->Position.y = Position.y + FieldSize.y;
		MirrorModelB->RotationX = RotationX;
		MirrorModelB->RotationY = RotationY;
		MirrorModelB->RotationZ = RotationZ;
		MirrorModelB->ModelColor = ModelColor;
		MirrorModelB->ModelScale = ModelScale;
		MirrorModelB->Enabled = Enabled;

		if (IsParent)
		{
			for (auto child : MirrorModelB->Children)
			{
				child->Enabled = MirrorModelB->Enabled;
			}
		}
	}
	else
	{
		MirrorModelB->Enabled = false;

		if (IsParent)
		{
			for (auto child : MirrorModelB->Children)
			{
				child->Enabled = MirrorModelB->Enabled;
			}
		}
	}

	//if (Position.y)

}

void Mirrored::Draw()
{
	Model3D::Draw();

}

void Mirrored::Disable()
{
	Enabled = false;
	MirrorModelT->Enabled = false;
	MirrorModelB->Enabled = false;
	MirrorModelL->Enabled = false;
	MirrorModelR->Enabled = false;
}

void Mirrored::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}