#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

void Base::SetTurretModel(Model& model)
{
	TurretModel = model;
}

void Base::SetPlayer(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

void Base::SetArrowModel(Model& model)
{
	TheManagers.EM.AddModel3D(RadarArrow = DBG_NEW Radar(), model);
	Color white = WHITE;
	RadarArrow->SetColor(white);
}

bool Base::Initialize(Utilities* utilities)
{
	Enemy::Initialize(utilities);

	Radius = 45;
	ShotTimerTime = 3.25f;

	return true;
}

bool Base::BeginRun()
{
	Enemy::BeginRun();

	for (int i = 0; i < 8; i++)
	{
		TheManagers.EM.AddModel3D(Turrets[i] = new Turret(), TurretModel);
		Turrets[i]->Initialize(TheUtilities);
		Turrets[i]->SetPlayer(ThePlayer);
		Turrets[i]->SetShotModel(ShotModel);
		Turrets[i]->BeginRun();
		Turrets[i]->SetParent(this);
		// Have to do for all of the mirrors too.
		Turrets[i]->MirrorModelT->SetParent(MirrorModelT);
		Turrets[i]->MirrorModelB->SetParent(MirrorModelB);
		Turrets[i]->MirrorModelL->SetParent(MirrorModelL);
		Turrets[i]->MirrorModelR->SetParent(MirrorModelR);
		Turrets[i]->MirrorModelTL->SetParent(MirrorModelTL);
		Turrets[i]->MirrorModelBL->SetParent(MirrorModelBL);
		Turrets[i]->MirrorModelTR->SetParent(MirrorModelTR);
		Turrets[i]->MirrorModelBR->SetParent(MirrorModelBR);
	}

	Turrets[0]->Position = { 73.5f - 50.0f, 93.5f - 50.0f, -200.0f};
	Turrets[1]->Position = { 93.5f - 50.0f, 73.5f - 50.0f, -200.0f};

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

	for (auto turret : Turrets)
	{
		turret->SetPosition(turret->Position);
	}

	RotationVelocityZ = 0.05f;

	return true;
}

void Base::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	RadarArrow->Position = ThePlayer->Position;
	RadarArrow->Enabled = Enabled;
	Vector3 arrowTarget = CheckOtherForPlayerSide(ThePlayer->Position, Position);

	RadarArrow->SetTarget(arrowTarget);

	Vector3 target = CheckOtherSide(ThePlayer->Position);

	for (auto turret : Turrets)
	{
		turret->RotationZ = turret->GetAngleFromVectorsZ(turret->WorldPosition,
			target) - RotationZ;

		turret->SetRotation(turret->RotationZ);
	}

	if (!UpdatedAfterSpawn) UpdateAfterSpawn();
}

void Base::Draw()
{
	Enemy::Draw();

}

void Base::Spawn(Vector3 position)
{
	Enabled = true;
	UpdatedAfterSpawn = false;
	Position = position;
	Z(-200.0f);

	for (auto turret : Turrets)
	{
		//turret->SetEnabled(false);
	}

}

void Base::DropOffOre()
{
	if (AmountOfOre < 8) Turrets[AmountOfOre]->SetEnabled(true);

	AmountOfOre++;
}

void Base::Fire(Vector3 velocity)
{
	Enemy::Fire();

	Enemy::Fire(Position, velocity);
}

void Base::UpdateAfterSpawn()
{
	UpdatedAfterSpawn = true;

	for (auto turret : Turrets)
	{
		turret->MirrorModelB->Enabled = MirrorModelB->Enabled;
		turret->MirrorModelT->Enabled = MirrorModelT->Enabled;
		turret->MirrorModelBR->Enabled = MirrorModelBR->Enabled;
		turret->MirrorModelBL->Enabled = MirrorModelBL->Enabled;
		turret->MirrorModelTR->Enabled = MirrorModelTR->Enabled;
		turret->MirrorModelTL->Enabled = MirrorModelTL->Enabled;
		turret->MirrorModelL->Enabled = MirrorModelL->Enabled;
		turret->MirrorModelR->Enabled = MirrorModelR->Enabled;
	}
}
