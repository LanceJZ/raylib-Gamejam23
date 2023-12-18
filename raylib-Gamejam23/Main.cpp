#pragma warning ( push )
#pragma warning ( disable : 26495 )

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "raylib.h"
#include "Game.h"
#include "glfw/glfw3.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

Managers TheManagers = {};
Vector2 FieldSize = {};

int main()
{
	static Game game;

	int windowHeight = 960; //height
	int windowWidth = 1280; //width

	InitWindow(windowWidth, windowHeight, "Game Jam 23");
	InitAudioDevice();

	Image icon = LoadImage("icon.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);

	if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
	glfwSwapInterval(0);
	SetTargetFPS(120);

	static Camera TheCamera = {};
	static Utilities TheUtilities = {};
	static GameLogic* Logic = {};

	TheManagers.EM.SetUtilities(&TheUtilities);
	TheManagers.EM.SetCamera(&TheCamera);

	// Define the camera to look into our 3D world
	TheCamera.position = { 0.0f, 0.0f, -500.0f };  // Camera position
	TheCamera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	TheCamera.up = { 0.0f, -1.0f, 0.0f };          // Camera up vector (rotation towards target)
	TheCamera.fovy = (float)GetScreenHeight();		//Camera/World space is screen space.
	TheCamera.projection = CAMERA_ORTHOGRAPHIC;   // Camera mode type

	game.Initialize(TheCamera, TheUtilities, Logic);
	game.Load();
	game.BeginRun();

	while (!WindowShouldClose())
	{
		game.ProcessInput();
		game.Update(GetFrameTime());
		BeginDrawing();
		ClearBackground({ 8, 2, 16, 100 });
		game.Draw();
#ifdef _DEBUG
		DrawFPS(5, 5);
#endif
		EndDrawing();
	}

	UnloadImage(icon);

	CloseWindow();
	CloseAudioDevice();
}