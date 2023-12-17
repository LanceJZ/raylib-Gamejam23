#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "ShotMaster.h"

class EnemyBase : public Model3D
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	std::vector<ShotMaster*> Shots;

	void SetManagers(Managers* man);
	void SetShotModel(Model& shotModel);

	virtual bool Initialize(Utilities* utils);
	virtual bool BeginRun();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:

	Model* ShotModel = {};
	void Fire();
};
