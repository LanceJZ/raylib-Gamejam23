#include "Utilities.h"

Utilities::Utilities()
{
	Random19937.seed(time(nullptr));
}

float Utilities::GetRandomFloat(float min, float max)
{
	if (min > max)
	{
		TraceLog(LOG_INFO, "*****\n");
		TraceLog(LOG_INFO, "********* GetRandomFloat used with min more than max *********\n");
		return 0;
	}

	if (false)
	{
		//Old Random Number Generator.
		std::default_random_engine randEngine(RandomDevice());
		std::uniform_real_distribution<float> urdRand(min, max);

		return urdRand(randEngine);
	}
	else if (true)
	{
		std::uniform_real_distribution<> urd(min, max);

		return urd(Random19937);
	}
	else
	{
		float rand = 0;
		float acc = 1000.0f;

		return GetRandomValue(min * acc, max * acc) / acc;
	}
}
