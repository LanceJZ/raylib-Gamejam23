#pragma once
#include "Globals.h"
#include "Model3D.h"

class Radar : public Model3D
{
public:
	Radar();
	virtual ~Radar();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

	void SetTarget(Vector3& target);

private:
	Vector3 Target = {};

};
