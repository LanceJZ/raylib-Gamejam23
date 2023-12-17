#pragma once
#include <memory>
#include "Globals.h"
#include "Utilities.h"
#include "Common.h"
#include "Managers.h"
#include "GameLogic.h"
#include "Background.h"
#include "Player.h"
#include "EnemyControl.h"

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

	bool Initialize(Camera &camera,
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
	size_t EnemiesID = 0;

	Vector2 FieldSize = {};
	//When adding classes to EM, must be heap pointer.
	Camera* Cam = {};
	GameLogic* Logic = {};

	Background* BackGround = {};
	Player* ThePlayer = {};
	EnemyControl* Enemies = {};

	void GameInput();
	void Draw3D();
	void Draw2D();
	void NewGame();
};

