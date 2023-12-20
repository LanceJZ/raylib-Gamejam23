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

	std::vector<Rock*> Rocks;

	void SetRocks(std::vector<Rock*> rocks);

	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:
	size_t MineTimer = {};
	size_t BumpTimer = {};

	bool WaypointReached = {};
	bool WasBumped = {};
	bool HasOre = {};

	AIState InState = {};

	float Thrust = 30.666f;

	Rock* rockToMine = {};

	void Search();
	Rock* FindCloseRock();
	void GoToRock();
};
