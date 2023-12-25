#pragma once
#include "Globals.h"
#include "Common.h"
#include "Star.h"

class Background : public Common
{
public:
	Background();
	virtual ~Background();

	void SetStarsModelID(size_t modelID);
	bool Initialize(Utilities* utilities);
	bool BeginRun();

	void Update();

private:
	size_t StarModelID = {};

	std::vector<Star*> Stars;

	void BuildStars();
	void BuildBorders();
};

