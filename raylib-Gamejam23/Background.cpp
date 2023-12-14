#include "Background.h"

Background::Background()
{

}

Background::~Background()
{
}

void Background::SetStarsModelID(size_t modelID)
{
	StarModelID = modelID;
}

void Background::SetManagers(Managers* man)
{
	Man = man;
}

bool Background::Initialize(Utilities* utils)
{
	Common::Initialize(utils);

	return false;
}

bool Background::BeginRun()
{

	BuildStars();

	return false;
}

void Background::Update()
{

}

void Background::BuildStars()
{

	size_t numberToMake = 300;

	for (int i = 0; i < numberToMake; i++)
	{
		Stars.push_back(Man->EM.AddModel3D(Man->CM.GetModel(StarModelID)));

		int sw = GetScreenWidth() / 2;
		int sh = GetScreenHeight() / 2;

		float starX = GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f);
		float starY = GetRandomFloat(-FieldSize.y * 0.5f, FieldSize.y * 0.5f);

		Man->EM.Model3Ds[Stars[i]]->TheColor = GetRandomColor();
		Man->EM.Model3Ds[Stars[i]]->Initialize(nullptr);
		Man->EM.Model3Ds[Stars[i]]->Position = {starX, starY, 10.0f};
		Man->EM.Model3Ds[Stars[i]]->ModelColor =
			{ (unsigned char)GetRandomValue(10, 200),
			(unsigned char)GetRandomValue(10, 200),
			(unsigned char)GetRandomValue(10, 200), 255 };
		Man->EM.Model3Ds[Stars[i]]->RotationAxis = { 1, 1, 1 };
		Man->EM.Model3Ds[Stars[i]]->RotationVelocity = GetRandomFloat(-16.66f, 16.666f);
	}
}
