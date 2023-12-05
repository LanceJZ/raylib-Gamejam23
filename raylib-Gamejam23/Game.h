#pragma once
#include <memory>
#include "Utilities.h"
#include "Common.h"
#include "Managers.h"
#include "GameLogic.h"

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
	Camera TheCamera = { 0 };

	bool Initialize(Camera &camera);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

private:
	size_t LogicID;

	Utilities Utils;
	Managers Man;
	GameLogic Logic;

	void NewGame();
	void Draw3D();
	void Draw2D();
};

