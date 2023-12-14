#pragma once
#include "ContentManager.h"
#include "EntityManager.h"

class Managers : Common
{
public:
	ContentManager CM;
	EntityManager EM;


	Managers();
	virtual ~Managers();

	bool Initialize(Utilities* utilities);
	bool BeginRun();
	bool SetCamera(Camera* camera);

	virtual void Update(float deltaTime);

private:

};