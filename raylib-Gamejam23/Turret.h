#pragma once
#include "Globals.h"
#include "Enemy.h"

class Turret : public Enemy
{
public:
	Turret();
	virtual ~Turret();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:

	void FireAtPlayer();
	void Fire(Vector3 velocity);

};
