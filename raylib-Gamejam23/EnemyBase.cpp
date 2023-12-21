#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::SetPlayer(Player* player)
{
	ThePlayer = player;
}

void EnemyBase::SetShotModel(Model &shotModel)
{
	ShotModel = ShotModel;
}

bool EnemyBase::Initialize(Utilities* utils)
{
	Model3D::Initialize(utils);

	return false;
}

bool EnemyBase::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void EnemyBase::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (X() > FieldSize.x * 0.5f) X(-FieldSize.x * 0.5f);

	if (X() < -FieldSize.x * 0.5f) X(FieldSize.x * 0.5f);

	if (Y() > FieldSize.y * 0.5f) Y(-FieldSize.y * 0.5f);

	if (Y() < -FieldSize.y * 0.5f) Y(FieldSize.y * 0.5f);
}

void EnemyBase::Draw()
{
	Model3D::Draw();

}

void EnemyBase::Spawn(Vector3 position)
{
	Position = position;
	Enabled = true;
}

void EnemyBase::Fire()
{
	bool spawnNewShot = true;
	size_t shotNumber = Shots.size();

	for (size_t shotCheck = 0; shotCheck < shotNumber; shotCheck++)
	{
		if (!Shots[shotCheck]->Enabled)
		{
			spawnNewShot = false;
			shotNumber = shotCheck;
			break;
		}
	}

	if (spawnNewShot)
	{
		//When adding as a new class, make sure to use DBG_NEW.
		Shots.push_back(DBG_NEW ShotMaster());
		TheManagers.EM.AddModel3D(Shots[shotNumber]);
		Shots[shotNumber]->SetModel(ShotModel, 2.5f);
		Shots[shotNumber]->Initialize(TheUtilities);
		Shots[shotNumber]->BeginRun();
	}

	float speed = 600.0f;
	float timer = 1.0f;
	Vector3 drift = { 0.01f, 0.01f, 0.01f };

	Shots[shotNumber]->Spawn(Position,
		Vector3Add(Velocity, VelocityFromAngleZ(speed)), timer);
}
