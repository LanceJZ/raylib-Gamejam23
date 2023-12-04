#include "Managers.h"

Managers::Managers()
{
}

Managers::~Managers()
{
}

bool Managers::Initialize(Utilities* utilities)
{
	CM.Initialize();
	EM.Initialize(utilities);

	return false;
}

bool Managers::BeginRun(Camera* camera)
{
	CM.BeginRun();
	EM.BeginRun(camera);

	return false;
}

void Managers::Update(float deltaTime)
{

}