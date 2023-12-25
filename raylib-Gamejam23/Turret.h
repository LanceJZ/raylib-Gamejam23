#pragma once
#include "Globals.h"
#include "Enemy.h"

class Turret : public Enemy
{
public:
	Turret();
	virtual ~Turret();

	Vector3 WorldPosition;

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:

	void PointAtPlayer();

};
