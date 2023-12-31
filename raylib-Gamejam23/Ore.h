#pragma once
#include "Globals.h"
#include "Mirrored.h"
#include "Player.h"

class Ore : public Mirrored
{
public:
	Ore();
	virtual ~Ore();

	bool Grabbed = false;

	void SetPlayer(Player* player);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);
	int GetOreType() const;

private:
	int Type = 0;
	Player* ThePlayer = {};

	bool CheckCollision();
};
