#pragma once
#include <memory>
#include "Utilities.h"
#include "Common.h"
#include "Managers.h"

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
	Utilities Utils;
	Managers Man;

	void NewGame();
	void Draw3D();
	void Draw2D();
};

