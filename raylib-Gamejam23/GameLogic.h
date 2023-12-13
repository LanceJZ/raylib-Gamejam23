#pragma once
#include "Common.h"
#include "Utilities.h"
#include "Player.h"

class GameLogic : public Common
{
public:
	GameLogic();
	virtual ~GameLogic();

	Vector2 FieldSize = {};

	void SetCamera(Camera* cam);
	void SetPlayer(Player* thePlayer);

	bool Initialize(Utilities* utils);
	bool BeginRun();

	void Input();
	void Update();

private:
	Camera* Cam = {};
	Player* ThePlayer = {};

	void PlayerOverEdge();
	void CameraUpdate();
};

