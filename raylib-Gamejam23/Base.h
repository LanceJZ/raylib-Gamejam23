#pragma once
#include "Globals.h"
#include "Model3D.h"

class Base : public Model3D
{
public:
	Base();
	virtual ~Base();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update(float deltaTime);
	void Draw();

	void Spawn(Vector3 position);

private:


};
