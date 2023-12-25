#include "ShotMaster.h"

ShotMaster::ShotMaster()
{
}

ShotMaster::~ShotMaster()
{
}

bool ShotMaster::Initialize(Utilities* utilities)
{
	Mirrored::Initialize(utilities);

	Radius = 2.5f;

	return false;
}

bool ShotMaster::BeginRun()
{
	Mirrored::BeginRun();

	TimerID = TheManagers.EM.AddTimer();

	return false;
}

void ShotMaster::Update(float deltaTime)
{
	Mirrored::Update(deltaTime);

	if (TheManagers.EM.Timers[TimerID]->Elapsed())
	{
		Disable();
	}
}

void ShotMaster::Draw()
{
	Mirrored::Draw();

}

void ShotMaster::Spawn(Vector3 position, Vector3 velocity, float timer)
{
	Mirrored::Spawn(position);

	Velocity = velocity;
	TheManagers.EM.Timers[TimerID]->Reset(timer);
}
