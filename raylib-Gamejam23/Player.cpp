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

void Player::Update(float deltaTime)
{
	Model3D::Update(deltaTime);

}

void Player::Draw()
{
	Model3D::Draw();

}
