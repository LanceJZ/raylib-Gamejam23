#pragma once
#include "Globals.h"
#include "Enemy.h"
#include "Base.h"

class EnemyThree : public Enemy
{
public:
	enum AIState
	{
		EvadePlayer,
		WaitForTime,
		GoToBase,
		Patrol,
		AttackPlayer,
	};

	EnemyThree();
	virtual ~EnemyThree();

	void SetBase(Base* base);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

private:
	size_t ThrustTimer = {};
	size_t WaypointNumber = 0;
	float Thrust = 0;
	Vector3 Waypoints[4] = {};

	AIState InState = {};

	Base* TheBase = {};

	void Evade(float deltaTime);
	void Wait(float deltaTime);
	void ReturnToBase(float deltaTime);
	void Patrolling(float deltaTime);
	void Attack(float deltaTime);
};
