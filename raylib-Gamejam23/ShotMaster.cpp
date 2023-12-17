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
	Enabled = true;
	Position = position;
	Velocity = velocity;
	TheManagers.EM.Timers[TimerID]->Reset(timer);
}
