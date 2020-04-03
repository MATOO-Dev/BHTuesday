#pragma once

#include "Defines.h"
#include "Wave.h"
#include <vector>

struct Level
{
	std::vector<Wave> mLevelWaves;
	bool mLevelFinished;
};