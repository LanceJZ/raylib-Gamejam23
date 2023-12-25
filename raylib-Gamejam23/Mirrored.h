#pragma once
#include "Globals.h"
#include "Player.h"

class Mirrored : public Model3D
{
public:
	Mirrored();
	virtual ~Mirrored();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

protected:
	Player* ThePlayer = {};
	Model3D* MirrorModelL = {};
	Model3D* MirrorModelR = {};

private:
	Vector2 AdjustedSize = {};

};
