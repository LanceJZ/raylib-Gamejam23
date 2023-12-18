#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

//Initialize Game
bool Game::Initialize(Camera &camera,
	Utilities &utilities, GameLogic* gameLogic)
{
	TheUtilities = &utilities;
	Cam = &camera;
	Logic = gameLogic;

	Common::Initialize(&utilities);
	//https://itch.io/jam/raylib-slo-jam
	SetWindowTitle("Knightmare Game for raylib Game Jam");

	FieldSize = { GetScreenWidth() * 3.0f, GetScreenHeight() * 3.0f };

	//When adding classes to EM, must be pointer to heap,IE: Name = new Class().
	LogicID = TheManagers.EM.AddCommon(Logic = DBG_NEW GameLogic());
	BackGroundID = TheManagers.EM.AddCommon(BackGround = DBG_NEW Background());
	EnemiesID = TheManagers.EM.AddCommon(Enemies = DBG_NEW EnemyControl());
	PlayerID = TheManagers.EM.AddModel3D(ThePlayer = DBG_NEW Player());

	Logic->SetCamera(Cam);
	Logic->SetPlayer(ThePlayer);

	Enemies->SetPlayer(ThePlayer);

	//Any Entities added after this point need this method fired manually.
	TheManagers.Initialize();

	return true;
}

bool Game::Load()
{
	size_t cubeID = TheManagers.CM.LoadTheModel("Cube");

	ThePlayer->SetModel(TheManagers.CM.LoadAndGetModel("Player Ship"), 1.0f);
	ThePlayer->SetFlameModel(TheManagers.EM.CreateModel3D(
		TheManagers.CM.LoadAndGetModel("Player Flame")));
	ThePlayer->SetShotModel(TheManagers.CM.GetModel(cubeID));
	BackGround->SetStarsModelID(cubeID);
	Enemies->SetEnemyOneModel(TheManagers.CM.LoadAndGetModel("EnemyOne"));
	Enemies->SetShotModel(TheManagers.CM.GetModel(cubeID));

	return true;
}

bool Game::BeginRun()
{
	//Any Entities added after this point need this method fired manually.
	TheManagers.BeginRun();

	NewGame();

	return true;
}

void Game::ProcessInput()
{
	GameInput();
	TheManagers.EM.Input();
}


void Game::Update(float deltaTime)
{
	if (State == Pause)
		return;

	TheManagers.EM.Update(deltaTime);
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
	TheManagers.EM.Draw3D();

#ifdef _DEBUG
	Vector2 fs = { FieldSize.x * 0.5f, FieldSize.y * 0.5f };

	DrawLine(-fs.x, -fs.y, fs.x, -fs.y, { DARKBLUE });
	DrawLine(fs.x, -fs.y, fs.x, fs.y, { DARKBLUE });
	DrawLine(fs.x, fs.y, -fs.x, fs.y, { DARKBLUE });
	DrawLine(-fs.x, fs.y, -fs.x, -fs.y, { DARKBLUE });
#endif
}

void Game::Draw2D()
{

}

void Game::NewGame()
{
	State = InPlay;

}