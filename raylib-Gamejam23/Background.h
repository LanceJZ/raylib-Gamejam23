#pragma once
#include "Globals.h"
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
	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:
	size_t StarModelID = {};

	std::vector<size_t> Stars;

	void BuildStars();
};

