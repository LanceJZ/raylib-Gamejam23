#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "ShotMaster.h"
#include "Player.h"

class EnemyBase : public Model3D
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	std::vector<ShotMaster*> Shots;

	bool Hit = false;

	void SetPlayer(Player* player);
	void SetShotModel(Model &shotModel);

	virtual bool Initialize(Utilities* utils);
	virtual bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

protected:
	Player* ThePlayer = {};

	void Fire();

private:

	Model ShotModel = {};

};
