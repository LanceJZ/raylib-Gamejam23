#pragma once
#include "Globals.h"
#include "Enemy.h"
#include "Turret.h"
#include "Radar.h"

class Base : public Enemy
{
public:
	Base();
	virtual ~Base();

	Turret* Turrets[8] = {};

	void SetTurretModel(Model& model);
	void SetPlayer(Player* thePlayer);
	void SetArrowModel(Model& model);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	void DropOffOre();

private:
	int AmountOfOre = 0;

	Model TurretModel = {};
	Player* ThePlayer = {};
	Radar* RadarArrow = {};

	void Fire(Vector3 velocity);

};
