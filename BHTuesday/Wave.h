#pragma once

#include "Defines.h"
#include "CEnemy.h"
#include "EnemySubclassIncluder.h"
#include <vector>

struct Wave
{
	std::vector<CEnemy*> mWaveEnemys;
	bool mWaveFinished = false;
	~Wave();
	void Add(CEnemy* enemyToAdd);
	void Remove();
	void Clear();
};