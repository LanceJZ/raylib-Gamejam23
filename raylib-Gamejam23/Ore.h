#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "Managers.h"
#include "Player.h"

class Ore : public Model3D
{
public:
	Ore();
	virtual ~Ore();

	void SetPlayer(Player* player);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);

private:

	Player* ThePlayer = {};
};
