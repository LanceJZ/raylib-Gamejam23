#include "Managers.h"

Managers::Managers()
{
}

Managers::~Managers()
{
}

bool Managers::Initialize()
{
	CM.Initialize();

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