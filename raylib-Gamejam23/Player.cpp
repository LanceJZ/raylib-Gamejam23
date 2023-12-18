#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetFlameModel(Model3D* flameModel)
{
	FlameModel = flameModel;
}

void Player::SetShotModel(Model& shotModel)
{
	ShotModel = &shotModel;
}

bool Player::Initialize(Utilities* utilities)
{
	Model3D::Initialize(utilities);

	Radius = 18.0f;

	//Enemy Spawn Test.
	//X(1300);
	//Y(980);
	//X(-1300);
	//Y(-980);
	//X(1000);
	//Y(900);
	//X(-1000);
	//Y(-900);

	return false;
}

bool Player::BeginRun()
{
	Model3D::BeginRun();

	FlameModel->X(-30.0f);
	FlameModel->RotationVelocityX = 50.0f;
	AddChild(FlameModel);

	return false;
}

void Player::Input()
{
	Model3D::Input();

	Keyboard();

	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
}

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

	if (!ThrustIsOn)
	{
		ThrustOff(deltaTime);
	}
	else if (ThrustIsOn && Enabled)
	{
		ThrustOn(deltaTime);
	}
}

void Player::Draw()
{
	Model3D::Draw();

}

bool Player::GetShieldIsOn()
{
	return false;
}

bool Player::ShieldHit(Vector3 hitByPos, Vector3 hitByVel)
{
	return false;
}

void Player::Hit()
{
	Acceleration = { 0 };
	Velocity = { 0 };
	Lives--;
	Enabled = false;
	ThrustIsOn = false;
}

void Player::ScoreUpdate(int addToScore)
{
	Score += addToScore;

	if (Score > HighScore)
	{
		HighScore = Score;
	}

	if (Score > NextNewLifeScore)
	{
		NextNewLifeScore += 10000;
		Lives++;
		NewLife = true;
	}
}

void Player::Reset()
{
	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;
}

void Player::NewGame()
{
	Lives = 4;
	NextNewLifeScore = 10000;
	Score = 0;
	Wave = 0;
	GameOver = false;
	Reset();
}

void Player::ThrustOn(float deltaTime)
{
	Acceleration = AccelerationToMaxAtRotation(540.666f, 0.001f, deltaTime);
	FlameModel->Enabled = true;
}

void Player::ThrustOff(float deltaTime)
{
	Acceleration = DecelerationToZero(0.75f, deltaTime);
	FlameModel->Enabled = false;

	float flameRot = 0;

	if (GetRandomValue(1, 10) < 5)
	{
		flameRot = GetRandomFloat(-50.0f, -25.0f);
	}
	else
	{
		flameRot = GetRandomFloat(25.0f, 50.0f);
	}

	FlameModel->RotationVelocityX = flameRot;
}

void Player::RotateLeft()
{
	RotationVelocity = -velocityRotZ;
}

void Player::RotateRight()
{
	RotationVelocity = velocityRotZ;
}

void Player::Fire()
{
	bool spawnNew = true;
	size_t spawnNumber = Shots.size();

	for (size_t check = 0; check < spawnNumber; check++)
	{
		if (!Shots[check]->Enabled)
		{
			spawnNew = false;
			spawnNumber = check;
			break;
		}
	}

	if (spawnNew)
	{
		//When adding as a new class, make sure to use DBG_NEW.
		Shots.push_back(DBG_NEW ShotMaster());
		TheManagers.EM.AddModel3D(Shots[spawnNumber], *ShotModel, 2.5f);
		Shots[spawnNumber]->Initialize(TheUtilities);
		Shots[spawnNumber]->BeginRun();
	}

	float speed = 600.0f;
	float timer = 1.0f;
	Vector3 drift = { 0.01f, 0.01f, 0.01f };

	Shots[spawnNumber]->Spawn(Position,
		Vector3Add(Velocity, VelocityFromAngleZ(speed)), timer);
}

void Player::ShieldOn()
{
}

void Player::ShieldOff()
{
}

void Player::Gamepad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
		RotateLeft();
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
		RotateRight();
	}

	if (IsGamepadButtonPressed(0, 7))
	{
		Fire();
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}

void Player::Keyboard()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		RotateRight();
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		RotateLeft();
	}
	else
	{
		RotationVelocity = 0;
	}

	if (IsKeyDown(KEY_UP))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
		Fire();
	}

	if (IsKeyDown(KEY_DOWN))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}
