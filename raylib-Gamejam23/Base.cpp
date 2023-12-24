#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

void Base::SetTurretModel(Model& turretModel)
{
	TurretModel = turretModel;
}

void Base::SetPlayer(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

bool Base::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	Radius = 45;
	Z(-50.0f);

	return false;
}

bool Base::BeginRun()
{
	Model3D::BeginRun();

	for (int i = 0; i < 8; i++)
	{
		TheManagers.EM.AddModel3D(Turrets[i] = new Turret(), TurretModel);
		Turrets[i]->Initialize(TheUtilities);
		Turrets[i]->SetPlayer(ThePlayer);
		Turrets[i]->BeginRun();
		Turrets[i]->Cull = false;
		AddChild(Turrets[i]);
	}

	RotationVelocityZ = 0.05f; //Need to fix child rotation, not quite right.

	return false;
}

void Base::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	for (auto turret : Turrets)
	{
		//turret->RotationVelocityZ = Common::RotateTowardsTargetZ(Position,
		//	ThePlayer->Position, turret->RotationZ, 0.5f);

		turret->RotationZ = turret->GetAngleFromVectorsZ(Position,
			ThePlayer->Position) - RotationZ;
	}
}

void Base::Draw()
{
	Model3D::Draw();

}

void Base::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;

	Turrets[0]->Position = { 73.5f - 50.0f, 93.5f - 50.0f, 0.0f};
	Turrets[1]->Position = { 93.5f - 50.0f, 73.5f - 50.0f, 0.0f};

	Turrets[2]->Position = Turrets[0]->Position;
	Turrets[2]->X(Turrets[2]->Position.x *= -1);

	Turrets[3]->Position = Turrets[1]->Position;
	Turrets[3]->X(Turrets[3]->Position.x *= -1);

	Turrets[4]->Position = Turrets[0]->Position;
	Turrets[4]->Y(Turrets[4]->Position.y *= -1);

	Turrets[5]->Position = Turrets[1]->Position;
	Turrets[5]->Y(Turrets[5]->Position.y *= -1);

	Turrets[6]->Position = Turrets[4]->Position;
	Turrets[6]->X(Turrets[6]->Position.x *= -1);

	Turrets[7]->Position = Turrets[5]->Position;
	Turrets[7]->X(Turrets[7]->Position.x *= -1);
}

void Base::DropOffOre()
{
	AmountOfOre++;
}
