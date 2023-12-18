#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "Managers.h"

class ShotMaster : public Model3D
{
public:
	ShotMaster();
	virtual ~ShotMaster();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position, Vector3 velocity, float timer);

private:
	size_t TimerID = 0;

};