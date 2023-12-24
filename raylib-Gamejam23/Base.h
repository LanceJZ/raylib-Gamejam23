#pragma once
#include "Globals.h"
#include "Turret.h"

class Base : public Model3D
{
public:
	Base();
	virtual ~Base();

	Turret* Turrets[8] = {};

	void SetTurretModel(Model& turretModel);
	void SetPlayer(Player* thePlayer);

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
};
