#pragma once
#include <memory>
#include "Utilities.h"
#include "Common.h"
#include "Managers.h"
#include "GameLogic.h"
#include "Background.h"
#include "Player.h"

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};

class Game : Common
{
public:
	Game();
	virtual ~Game();

	bool PlayBackgroundMusic = true;
	GameState State = MainMenu;

	bool Initialize(Camera &camera, Managers &managers,
		Utilities &utilities, GameLogic* gameLogic);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

private:
	size_t LogicID = 0;
	size_t BackGroundID = 0;
	size_t PlayerID = 0;

	Vector2 FieldSize = {};
	//When adding classes to EM, must be pointer, new {Class}.
	Camera* Cam = {};
	Utilities* Utils = {};
	Managers* Man = {};
	GameLogic* Logic = {};

	Background* BackGround = {};
	Player* ThePlayer = {};

	void GameInput();
	void Draw3D();
	void Draw2D();
	void NewGame();
};

