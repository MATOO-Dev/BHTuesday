#pragma once

#include "Defines.h"
#include "CEnemy.h"
#include <vector>

struct Wave
{
	std::vector<CEnemy*> mWaveEnemys;
	bool mWaveFinished;
	void Add(CEnemy* enemyToAdd);
	void Remove();
	void Clear();
};

void Wave::Add(CEnemy* enemyToAdd)
{
	mWaveEnemys.push_back(enemyToAdd);
}

void Wave::Remove()
{

}

void Wave::Clear()
{
	mWaveEnemys.clear();
}