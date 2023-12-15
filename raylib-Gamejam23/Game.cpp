#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}
//Initialize Game
bool Game::Initialize(Camera &camera, Managers &managers,
	Utilities &utilities, GameLogic* gameLogic)
{
	Man = &managers;
	Utils = &utilities;
	Cam = &camera;
	Logic = gameLogic;

	Common::Initialize(Utils);

	SetWindowTitle("Knightmare Game for raylib Game Jam");

	FieldSize = { GetScreenWidth() * 3.0f, GetScreenHeight() * 3.0f };

	//When adding classes to EM, must be pointer to heap,IE: Name = new Class().
	LogicID = Man->EM.AddCommon(Logic = new GameLogic());
	BackGroundID = Man->EM.AddCommon(BackGround = new Background());
	PlayerID = Man->EM.AddModel3D(ThePlayer = new Player());

	Logic->SetCamera(Cam);
	Logic->SetPlayer(ThePlayer);
	Logic->FieldSize = FieldSize;

	BackGround->SetManagers(Man);
	BackGround->FieldSize = FieldSize;

	ThePlayer->SetManagers(Man);

	//Any Entities added after this point need this method fired manually.
	Man->Initialize();

	return true;
}

bool Game::Load()
{
	size_t cubeID = Man->CM.LoadTheModel("Cube");

	ThePlayer->SetModel(Man->CM.LoadAndGetModel("Player Ship"), 1.0f);
	ThePlayer->SetFlameModel(Man->EM.CreateModel3D(
		Man->CM.LoadAndGetModel("Player Flame")));
	ThePlayer->SetShotModel(Man->CM.GetModel(cubeID));
	BackGround->SetStarsModelID(cubeID);

	return true;
}

bool Game::BeginRun()
{
	//Any Entities added after this point need this method fired manually.
	Man->BeginRun();

	NewGame();

	return true;
}

void Game::ProcessInput()
{
	GameInput();
	Man->EM.Input();
}


void Game::Update(float deltaTime)
{
	if (State == Pause)
		return;

	Man->EM.Update(deltaTime);
}

void Game::Draw()
{
	BeginMode3D(*Cam);
	//3D Drawing here.
	Draw3D();
	EndMode3D();
	//2D drawing, fonts go here.
	Draw2D();
}

void Game::GameInput()
{
	if (State == MainMenu)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}

		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsKeyPressed(KEY_D))
		{

		}
	}

	if (State == InPlay)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = Pause;
			}

			if (IsGamepadButtonPressed(0, 8)) //X button
			{
				PlayBackgroundMusic = !PlayBackgroundMusic;
			}
		}

		if (IsKeyPressed(KEY_M))
		{
			PlayBackgroundMusic = !PlayBackgroundMusic;
		}


		if (IsKeyPressed(KEY_P))
		{
			State = Pause;
		}
	}
	else if (State == Pause)
	{
		if (IsKeyPressed(KEY_P))
		{
			State = InPlay;
		}

		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = InPlay;
			}
		}
	}
}

void Game::Draw3D()
{
	Man->EM.Draw3D();
}

void Game::Draw2D()
{

}

void Game::NewGame()
{
	State = InPlay;

}