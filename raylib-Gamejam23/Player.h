#pragma once
#include "Model3D.h"

class Player : public Model3D
{
public:
	Player();
	virtual ~Player();

	bool NewLife = false;
	bool GameOver = true;

	int Wave { 0 };
	int Score { 0 };
	int HighScore { 0 };
	int Lives { 0 };

	bool Initialize(Utilities* utils);
	bool BeginRun(Camera* camera);

	void Input();
	void Update(float deltaTime);
	void Draw();

	bool GetShieldIsOn();
	bool ShieldHit(Vector3 hitByPos, Vector3 hitByVel);
	void Hit();
	void ScoreUpdate(int addToScore);
	void Reset();
	void NewGame();

private:
	bool ThrustIsOn = false;
	int NextNewLifeScore = 10000;
	float ThrustSoundTime = 0;
	float ShieldPower = 100;
	float velocityRotZ = 3.666f;

	void ThrustOn(float deltaTime);
	void ThrustOff(float deltaTime);
	void RotateLeft();
	void RotateRight();
	void Fire();
	void ShieldOn();
	void ShieldOff();
	void Gamepad();
	void Keyboard();

};
