#include "GameLogic.h"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::SetCamera(Camera* cam)
{
	Cam = cam;
}

void GameLogic::SetPlayer(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

bool GameLogic::Initialize(Utilities* utils)
{
	Common::Initialize(utils);

	return false;
}

bool GameLogic::BeginRun()
{

	return false;
}

void GameLogic::Input()
{

}

void GameLogic::Update()
{
	CameraUpdate();
	PlayerOverEdge();
}

void GameLogic::PlayerOverEdge()
{
	if (ThePlayer->X() > FieldSize.x * 0.5f) ThePlayer->X(-FieldSize.x * 0.5f);

	if (ThePlayer->X() < -FieldSize.x * 0.5f) ThePlayer->X(FieldSize.x * 0.5f);

	if (ThePlayer->Y() > FieldSize.y * 0.5f) ThePlayer->Y(-FieldSize.y * 0.5f);

	if (ThePlayer->Y() < -FieldSize.y * 0.5f) ThePlayer->Y(FieldSize.y * 0.5f);
}

void GameLogic::CameraUpdate()
{
	Cam->position.x = ThePlayer->Position.x;
	Cam->position.y = ThePlayer->Position.y;
	Cam->target.x = Cam->position.x;
	Cam->target.y = Cam->position.y;
}
