#include "Wave.h"

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