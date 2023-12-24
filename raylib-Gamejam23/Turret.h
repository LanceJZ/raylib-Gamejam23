#pragma once
#include "Globals.h"
#include "EnemyBase.h"

class Turret : public EnemyBase
{
public:
	Turret();
	virtual ~Turret();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:
	void PointAtPlayer();

};
