#pragma once
#include "EnemyBase.h"
#include "Rock.h"

class EnemyOne : public EnemyBase
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

	void SetRocks(std::vector<Rock*> rocks);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:
	size_t MineTimer = {};
	size_t BumpTimer = {};

	bool WasBumped = {};
	bool HasOre = {};

	AIState InState = {};

	float Thrust = 4.666f;
	float Deceleration = 0.125f;
	float MaxVelocity = 50;
	float MinVelocity = 3;

	Rock* RockToMine = {};
	std::vector<Rock*> Rocks;

	void Search();
	Rock* FindCloseRock();
	void HeadToRock(float deltaTime);
	void MineRock();

	bool CheckCollusion();
	bool CheckMining();
};
