#pragma once
#include "Common.h"
#include "Managers.h"
#include "Model3D.h"

class Background : public Common
{
public:
	Background();
	virtual ~Background();

	Vector2 FieldSize = {};

	void SetStarsModelID(size_t modelID);
	void SetCamera(Camera* cam);
	void SetManagers(Managers* man);
	bool Initialize(Utilities* utils);
	bool BeginRun();

	void Update();

private:
	size_t StarModelID = {};
	Managers* Man = {};
	Camera* Cam = {};
	std::vector<size_t> Stars;

	void BuildStars();
};

