#pragma once

#include "Defines.h"
#include "CEnemy.h"
#include <vector>

struct Wave
{
	std::vector<CEnemy*> mWaveEnemys;
	bool mWaveFinished;
	~Wave();
	void Add(CEnemy* enemyToAdd);
	void Remove();
	void Clear();
};