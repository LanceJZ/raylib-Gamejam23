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

void Background::SetCamera(Camera* cam)
{
	Cam = cam;
}

void Background::SetManagers(Managers* man)
{
	Man = man;
}

bool Background::Initialize(Utilities* utils)
{
	Common::Initialize(utils);

	FieldSize = { GetScreenWidth() * 3.0f, GetScreenHeight() * 3.0f };

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

		//star.X(100);
		//star.Y(100);


	size_t numberToMake = 100;

	for (int i = 0; i < numberToMake; i++)
	{
		Stars.push_back(Man->EM.AddModel3D(Man->CM.GetModel(StarModelID), 1.0f));

		int sw = GetScreenWidth() / 2;
		int sh = GetScreenHeight() / 2;

		float starX = GetRandomFloat(-FieldSize.x * 0.5f, FieldSize.x * 0.5f);
		float starY = GetRandomFloat(-FieldSize.y * 0.5f, FieldSize.y * 0.5f);

		Man->EM.Model3Ds[Stars[i]]->TheColor = GetRandomColor();
		Man->EM.Model3Ds[Stars[i]]->Initialize(nullptr);
		Man->EM.Model3Ds[Stars[i]]->BeginRun(Cam);
		Man->EM.Model3Ds[Stars[i]]->Position = {starX, starY, 10.0f};
	}
}
