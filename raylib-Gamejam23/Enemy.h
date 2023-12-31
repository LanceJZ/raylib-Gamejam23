#pragma once
#include "Globals.h"
#include "Mirrored.h"
#include "ShotMaster.h"
#include "Player.h"
#include "Radar.h"

class Enemy : public Mirrored
{
public:
	Enemy();
	virtual ~Enemy();

	std::vector<ShotMaster*> Shots;

	bool Hit = false;

	void SetPlayer(Player* player);
	void SetShotModel(Model &shotModel);
	void SetArrowModel(Model& arrowModel);

	virtual bool Initialize(Utilities* utilities);
	virtual bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

protected:
	size_t ShotTimer = 0;
	float ShotTimerTime = 0;

	Player* ThePlayer = {};
	Radar* RadarArrow = {};

	void Fire();

private:

	Model ShotModel = {};

};
