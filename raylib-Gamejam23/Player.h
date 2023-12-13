#pragma once
#include "Model3D.h"

class Player : public Model3D
{
public:
	Player();
	virtual ~Player();

	bool Initialize(Utilities* utils);
	bool BeginRun(Camera* camera);

	void Update(float deltaTime);
	void Draw();

private:

};
