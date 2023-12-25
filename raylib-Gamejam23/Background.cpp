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

bool Background::Initialize(Utilities* utilities)
{
	Common::Initialize(utilities);

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
		Stars.push_back(TheManagers.EM.AddModel3D(TheManagers.CM.GetModel(StarModelID),
			1.75f));

		int sw = GetScreenWidth() / 2;
		int sh = GetScreenHeight() / 2;

		float starX = GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f);
		float starY = GetRandomFloat(-FieldSize.y * 0.5f, FieldSize.y * 0.5f);

		TheManagers.EM.Model3Ds[Stars[i]]->Initialize(nullptr);
		TheManagers.EM.Model3Ds[Stars[i]]->Position = {starX, starY, 10.0f};
		TheManagers.EM.Model3Ds[Stars[i]]->RotationVelocityX =
			GetRandomFloat(-16.66f, 16.66f);
		TheManagers.EM.Model3Ds[Stars[i]]->RotationVelocityY =
			GetRandomFloat(-16.66f, 16.66f);
		TheManagers.EM.Model3Ds[Stars[i]]->RotationVelocityZ =
			GetRandomFloat(-16.66f, 16.66f);
		TheManagers.EM.Model3Ds[Stars[i]]->ModelColor =
			{
				(unsigned char)GetRandomValue(50, 200),
				(unsigned char)GetRandomValue(10, 100),
				(unsigned char)GetRandomValue(50, 200), 255
			};

	}
}

void Background::BuildBorders()
{
}
