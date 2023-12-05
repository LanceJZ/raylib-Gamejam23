#pragma once
#include "Common.h"

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update();

private:

};

