#pragma once

#include "Defines.h"
#include "CEnemy.h"
#include "Wave.h"
#include "Level.h"

class CLevelEditor
{
private:
	EEnemyType mSelectedEnemyType;
	Wave mCurrentWave;
	Level mCurrentLevel;
public:
	void PlaceEnemy();
	void FinishWave();
	void FinishLevel();
};

