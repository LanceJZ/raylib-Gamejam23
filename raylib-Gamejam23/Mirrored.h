#pragma once
#include "Globals.h"

class Mirrored : public Model3D
{
public:
	Mirrored();
	virtual ~Mirrored();

	Vector3 WorldPosition = {};
	Model3D* MirrorModelL = {};
	Model3D* MirrorModelR = {};
	Model3D* MirrorModelT = {};
	Model3D* MirrorModelB = {};
	Model3D* MirrorModelTR = {};
	Model3D* MirrorModelBR = {};
	Model3D* MirrorModelTL = {};
	Model3D* MirrorModelBL = {};

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

	void Disable();
private:
	Vector2 AdjustedSize = {};

};
