#pragma once
#include "EnemyBase.h"

class EnemyOne : public EnemyBase
{
public:
	EnemyOne();
	virtual ~EnemyOne();

	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

private:

};
