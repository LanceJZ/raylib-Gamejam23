#pragma once
#include "Enemy.h"
#include "Base.h"
#include "Rock.h"
#include "Ore.h"

class EnemyOne : public Enemy
{
	enum  AIState
	{
		Evade,
		FindRock,
		Wait,
		Mine,
		RetrieveOre,
		GoToRock,
		ReturnToBase
	};

public:
	EnemyOne();
	virtual ~EnemyOne();

	void SetBase(Base* base);
	void SetRocks(std::vector<Rock*> &rocks);
	void SetOre(std::vector<Ore*> &ore);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:
	bool WasBumped = {};
	bool HasOre = {};

	size_t MineTimer = {};
	size_t BumpTimer = {};
	size_t ThrustTimer = {};

	AIState InState = {};

	float Thrust = 10.666f;
	float Deceleration = 0.125f;
	float MaxVelocity = 50;
	float MinVelocity = 3;

	Vector3 OreInGraspPosition = {};

	Base* EnemyBase = {};
	Rock* RockToMine = {};
	std::vector<Rock*> Rocks;
	Ore* OreToGrab = {};
	std::vector<Ore*> OreCollection;

	void Search();
	Rock* GetNearbyRock();
	Ore* FindCloseOre();
	void HeadToRock(float deltaTime);
	void HeadToOre(float deltaTime);
	void HeadToBase(float deltaTime);
	void MineRock();

	bool CheckCollusion();
	bool CheckMining();
	bool CheckForOre();

	void Reset();
};
