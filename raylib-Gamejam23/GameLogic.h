#pragma once
#include "Common.h"
#include "Utilities.h"

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	bool Initialize(Utilities* utils);
	bool BeginRun();

	void Input();
	void Update();

private:

};

