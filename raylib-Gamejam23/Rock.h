#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "Managers.h"
#include "EnemyBase.h"

class Rock : public EnemyBase
{
public:
	Rock();
	virtual ~Rock();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:

	Managers* TheManagers = {};

};
