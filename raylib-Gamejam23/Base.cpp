#include "Base.h"

Base::Base()
{
}

Base::~Base()
{
}

bool Base::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	return false;
}

bool Base::BeginRun()
{
	Model3D::BeginRun();

	return false;
}

void Base::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Base::Draw()
{
	Model3D::Draw();

}

void Base::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;

// Turret positions relative to the center of the base.
//X 73.5
//Y -6.5
//X 93.5
//Y -26.5
}
