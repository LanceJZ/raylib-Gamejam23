#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Initialize(Utilities* utils)
{
	Model3D::Initialize(utils);

	return false;
}

bool Player::BeginRun(Camera* camera)
{
	Model3D::BeginRun(camera);

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
}

void Player::ThrustOff(float deltaTime)
{
	Acceleration = DecelerationToZero(0.75f, deltaTime);
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
