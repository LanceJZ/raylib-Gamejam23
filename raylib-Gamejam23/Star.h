#pragma once
#include "Globals.h"
#include "Mirrored.h"

class Star : public Mirrored
{
public:
	Star();
	virtual ~Star();

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Spawn(Vector3 position);

	void Update(float deltaTime);
	void Draw();

private:


};
