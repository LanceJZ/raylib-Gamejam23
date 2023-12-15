#include "ShotMaster.h"

ShotMaster::ShotMaster()
{
}

ShotMaster::~ShotMaster()
{
}

void ShotMaster::SetManagers(Managers* man)
{
	Man = man;
}

bool ShotMaster::Initialize(Utilities* utils)
{
	Model3D::Initialize(utils);

	return false;
}

bool ShotMaster::BeginRun()
{
	Model3D::BeginRun();

	TimerID = Man->EM.AddTimer();

	return false;
}

void ShotMaster::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (Man->EM.Timers[TimerID]->Elapsed())
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
	Position = position;
	Velocity = velocity;
	Man->EM.Timers[TimerID]->Reset(timer);
}
