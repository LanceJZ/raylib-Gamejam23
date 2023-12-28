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
	TheManagers.EM.AddModel3D(MirrorModelTR = new Model3D());
	TheManagers.EM.AddModel3D(MirrorModelBR = new Model3D());
	TheManagers.EM.AddModel3D(MirrorModelTL = new Model3D());
	TheManagers.EM.AddModel3D(MirrorModelBL = new Model3D());

	MirrorModelL->SetModel(GetModel());
	MirrorModelR->SetModel(GetModel());
	MirrorModelT->SetModel(GetModel());
	MirrorModelB->SetModel(GetModel());
	MirrorModelTL->SetModel(GetModel());
	MirrorModelTR->SetModel(GetModel());
	MirrorModelBL->SetModel(GetModel());
	MirrorModelBR->SetModel(GetModel());

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

	float sw = GetScreenWidth() * 0.5f;
	float sh = GetScreenWidth() * 0.5f;

	if (Position.x > AdjustedSize.x - sw)
	{
		MirrorModelL->Position.x = Position.x - FieldSize.x;
		MirrorModelL->Position.y = Position.y;
		MirrorModelL->RotationX = RotationX;
		MirrorModelL->RotationY = RotationY;
		MirrorModelL->RotationZ = RotationZ;
		MirrorModelL->ModelColor = ModelColor;
		MirrorModelL->ModelScale = ModelScale;
		MirrorModelL->Radius = Radius;
		MirrorModelL->Enabled = Enabled;
	}
	else
	{
		MirrorModelL->Enabled = false;
	}

	if (Position.x < (-AdjustedSize.x + sh))
	{
		MirrorModelR->Position.x = Position.x + FieldSize.x;
		MirrorModelR->Position.y = Position.y;
		MirrorModelR->RotationX = RotationX;
		MirrorModelR->RotationY = RotationY;
		MirrorModelR->RotationZ = RotationZ;
		MirrorModelR->ModelColor = ModelColor;
		MirrorModelR->ModelScale = ModelScale;
		MirrorModelR->Radius = Radius;
		MirrorModelR->Enabled = Enabled;
	}
	else
	{
		MirrorModelR->Enabled = false;
	}


	if (Position.y > (AdjustedSize.y - sh))
	{
		MirrorModelT->Position.x = Position.x;
		MirrorModelT->Position.y = Position.y - FieldSize.y;
		MirrorModelT->RotationX = RotationX;
		MirrorModelT->RotationY = RotationY;
		MirrorModelT->RotationZ = RotationZ;
		MirrorModelT->ModelColor = ModelColor;
		MirrorModelT->ModelScale = ModelScale;
		MirrorModelT->Radius = Radius;
		MirrorModelT->Enabled = Enabled;
	}
	else
	{
		MirrorModelT->Enabled = false;
	}

	if (Position.y < (-AdjustedSize.y + sh))
	{
		MirrorModelB->Position.x = Position.x;
		MirrorModelB->Position.y = Position.y + FieldSize.y;
		MirrorModelB->RotationX = RotationX;
		MirrorModelB->RotationY = RotationY;
		MirrorModelB->RotationZ = RotationZ;
		MirrorModelB->ModelColor = ModelColor;
		MirrorModelB->ModelScale = ModelScale;
		MirrorModelB->Radius = Radius;
		MirrorModelB->Enabled = Enabled;
	}
	else
	{
		MirrorModelB->Enabled = false;
	}

	if (Position.x > (AdjustedSize.x - sw) &&
		Position.y > (AdjustedSize.y - sh))
	{
		MirrorModelTL->Position.x = Position.x - FieldSize.x;
		MirrorModelTL->Position.y = Position.y - FieldSize.y;
		MirrorModelTL->RotationX = RotationX;
		MirrorModelTL->RotationY = RotationY;
		MirrorModelTL->RotationZ = RotationZ;
		MirrorModelTL->ModelColor = ModelColor;
		MirrorModelTL->ModelScale = ModelScale;
		MirrorModelTL->Radius = Radius;
		MirrorModelTL->Enabled = Enabled;
	}
	else
	{
		MirrorModelTL->Enabled = false;
	}

	if (Position.x > (AdjustedSize.x - sw) &&
		Position.y < (-AdjustedSize.y + sh))
	{
		MirrorModelBL->Position.x = Position.x - FieldSize.x;
		MirrorModelBL->Position.y = Position.y + FieldSize.y;
		MirrorModelBL->RotationX = RotationX;
		MirrorModelBL->RotationY = RotationY;
		MirrorModelBL->RotationZ = RotationZ;
		MirrorModelBL->ModelColor = ModelColor;
		MirrorModelBL->ModelScale = ModelScale;
		MirrorModelBL->Radius = Radius;
		MirrorModelBL->Enabled = Enabled;
	}
	else
	{
		MirrorModelBL->Enabled = false;
	}

	if (Position.x < (-AdjustedSize.x + sw) &&
		Position.y > (AdjustedSize.y - sh))
	{
		MirrorModelTR->Position.x = Position.x + FieldSize.x;
		MirrorModelTR->Position.y = Position.y - FieldSize.y;
		MirrorModelTR->RotationX = RotationX;
		MirrorModelTR->RotationY = RotationY;
		MirrorModelTR->RotationZ = RotationZ;
		MirrorModelTR->ModelColor = ModelColor;
		MirrorModelTR->ModelScale = ModelScale;
		MirrorModelTR->Radius = Radius;
		MirrorModelTR->Enabled = Enabled;
	}
	else
	{
		MirrorModelTR->Enabled = false;
	}

	if (Position.x < (-AdjustedSize.x + sw) &&
		Position.y < (-AdjustedSize.y + sh))
	{
		MirrorModelBR->Position.x = Position.x + FieldSize.x;
		MirrorModelBR->Position.y = Position.y + FieldSize.y;;
		MirrorModelBR->RotationX = RotationX;
		MirrorModelBR->RotationY = RotationY;
		MirrorModelBR->RotationZ = RotationZ;
		MirrorModelBR->ModelColor = ModelColor;
		MirrorModelBR->ModelScale = ModelScale;
		MirrorModelBR->Radius = Radius;
		MirrorModelBR->Enabled = Enabled;
	}
	else
	{
		MirrorModelBR->Enabled = false;
	}


	if (IsParent)
	{
		for (auto child : MirrorModelB->Children)
		{
			child->Enabled = MirrorModelB->Enabled;
		}

		for (auto child : MirrorModelT->Children)
		{
			child->Enabled = MirrorModelT->Enabled;
		}

		for (auto child : MirrorModelR->Children)
		{
			child->Enabled = MirrorModelR->Enabled;
		}

		for (auto child : MirrorModelL->Children)
		{
			child->Enabled = MirrorModelL->Enabled;
		}

		for (auto child : MirrorModelTL->Children)
		{
			child->Enabled = MirrorModelTL->Enabled;
		}

		for (auto child : MirrorModelBL->Children)
		{
			child->Enabled = MirrorModelBL->Enabled;
		}

		for (auto child : MirrorModelTR->Children)
		{
			child->Enabled = MirrorModelTR->Enabled;
		}

		for (auto child : MirrorModelBR->Children)
		{
			child->Enabled = MirrorModelBR->Enabled;
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
	MirrorModelTR->Enabled = false;
	MirrorModelBR->Enabled = false;
	MirrorModelTL->Enabled = false;
	MirrorModelBL->Enabled = false;
}

void Mirrored::Spawn(Vector3 position)
{
	Entity::Spawn(position);

}