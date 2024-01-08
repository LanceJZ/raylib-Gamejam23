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
	void SetShotModel(Model &model);
	void SetArrowModel(Model& model);

	virtual bool Initialize(Utilities* utilities);
	virtual bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

protected:
	size_t ShotTimer = 0;
	size_t ShotNumber = 0;
	float ShotTimerTime = 0;
	Model ShotModel = {};

	Player* ThePlayer = {};
	Radar* RadarArrow = {};

	void Fire();
	void Fire(Vector3 position, Vector3 velocity);

private:


};
