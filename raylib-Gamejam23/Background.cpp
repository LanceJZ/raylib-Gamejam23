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
		size_t star = Stars.size();

		Stars.push_back(DBG_NEW Star());
		TheManagers.EM.AddModel3D(Stars[i],
			TheManagers.CM.GetModel(StarModelID), 1.75f);

		int sw = GetScreenWidth() / 2;
		int sh = GetScreenHeight() / 2;

		float starX = GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f);
		float starY = GetRandomFloat(-FieldSize.y * 0.5f, FieldSize.y * 0.5f);

		Stars[i]->Initialize(nullptr);
		Stars[i]->Position = {starX, starY, 10.0f};
		Stars[i]->RotationVelocityX = GetRandomFloat(-16.66f, 16.66f);
		Stars[i]->RotationVelocityY = GetRandomFloat(-16.66f, 16.66f);
		Stars[i]->RotationVelocityZ = GetRandomFloat(-16.66f, 16.66f);
		Stars[i]->ModelColor =
			{
				(unsigned char)GetRandomValue(50, 200),
				(unsigned char)GetRandomValue(10, 100),
				(unsigned char)GetRandomValue(50, 200), 255
			};
		Stars[i]->BeginRun();
	}
}

void Background::BuildBorders()
{
}
