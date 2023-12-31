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
	void SetColor(Color& color);

private:
	int ScreenTop = 0;
	int FieldAdjusted = 0;
	Color ArrowColor = {};

	Vector3 Target = {};

};
