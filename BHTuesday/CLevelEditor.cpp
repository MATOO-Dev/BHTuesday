#include "CLevelEditor.h"

void CLevelEditor::PlaceEnemy()
{	
	//detect current enemy type, then create it and add to wave at clicked position
	switch (mSelectedEnemyType)
	{
	case EEnemyType::Null:
		//CSphere newSphere = CSphere();
		//currentWave.Add(newSphere);
		break;
	default:
		std::cout << "failed to get enemy type" << std::endl;
		break;
	}
}

void CLevelEditor::FinishWave()
{
	//adds wave to level and empties currently edited wave
	mCurrentLevel.mLevelWaves.push_back(mCurrentWave);
	mCurrentWave.Clear();
}

void CLevelEditor::FinishLevel()
{
	//finishes level by saving to file
}