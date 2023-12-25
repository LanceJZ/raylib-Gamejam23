#include "ShotMaster.h"

ShotMaster::ShotMaster()
{
}

ShotMaster::~ShotMaster()
{
}

bool ShotMaster::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	Radius = 2.5f;

	return false;
}

bool ShotMaster::BeginRun()
{
	Model3D::BeginRun();

	TimerID = TheManagers.EM.AddTimer();

	return false;
}

void ShotMaster::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (X() > FieldSize.x * 0.5f) X(-FieldSize.x * 0.5f);
	if (X() < -FieldSize.x * 0.5f) X(FieldSize.x * 0.5f);
	if (Y() > FieldSize.y * 0.5f) Y(-FieldSize.y * 0.5f);
	if (Y() < -FieldSize.y * 0.5f) Y(FieldSize.y * 0.5f);

	if (TheManagers.EM.Timers[TimerID]->Elapsed())
	{
		Enabled = false;
	}
}

void ShotMaster::Draw()
{
	Model3D::Draw();

}

void ShotMaster::Spawn(Vector3 position, Vector3 velocity, float timer)
{
	Entity::Spawn(position);

	Velocity = velocity;
	TheManagers.EM.Timers[TimerID]->Reset(timer);
}
