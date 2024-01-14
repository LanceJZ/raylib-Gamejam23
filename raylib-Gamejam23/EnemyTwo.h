#pragma once
#include "Globals.h"
#include "Enemy.h"
#include "EnemyOne.h"

enum  AIState
{
	EvadePlayer,
	SearchForDrone,
	WaitForTime,
	GoToDrone,
	Patrol,
	AttackPlayer,
};


class EnemyTwo : public Enemy
{
public:
	EnemyTwo();
	virtual ~EnemyTwo();

	void SetOnes(std::vector<EnemyOne*> &ones);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

private:
	size_t ThrustTimer = {};
	int WaypointNumber = 0;
	float Thrust = 0;

	AIState InState = {};

	Vector3 Waypoints[4] = {};

	EnemyOne* DroneProtecting = {};
	std::vector<EnemyOne*> Ones;

	void Evade(float deltaTime);
	void Runaway(float deltaTime);
	void Search(float deltaTime);
	void Wait(float deltaTime);
	void HeadToDrone(float deltaTime);
	void PatrolArea(float deltaTime);
	void Attack(float deltaTime);
	EnemyOne* FindDrone();
};
