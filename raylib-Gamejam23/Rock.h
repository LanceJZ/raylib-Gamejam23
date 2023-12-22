#pragma once
#include "Globals.h"
#include "Model3D.h"
#include "Managers.h"
#include "Player.h"

class Rock : public Model3D
{
public:
	Rock();
	virtual ~Rock();

	bool Hit = false;
	int Hardness = 0;

	void SetPlayer(Player* player);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	bool CheckCollision();
	int GetAmountOfOre() const;

private:
	int OreAmount = 0;

	Player* ThePlayer = {};
};
