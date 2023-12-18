#pragma once
#include "Globals.h"
#include "Common.h"
#include "Utilities.h"
#include "Player.h"

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	void SetCamera(Camera* cam);
	void SetPlayer(Player* thePlayer);

	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Input();
	void Update();

private:
	Camera* Cam = {};
	Player* ThePlayer = {};

	void PlayerOverEdge();
	void CameraUpdate();
};

