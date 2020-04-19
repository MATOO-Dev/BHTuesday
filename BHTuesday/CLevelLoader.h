#pragma once

#include "Defines.h"
#include "Level.h"
#include "EnemySubclassIncluder.h"
#include <SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class CLevelLoader
{
private:
	CPlayer* mPlayerRef;
	std::vector<CProjectile>& mEnemyBullets;
	SDL_Renderer* mRenderer;
	int waveAmount;
	Level loadingLevel;
	std::vector<std::string> fileLines;
	void ParseFile(std::string fileName);
	ELevelLoadAction GetLoadAction(std::string lineContent);
	EEnemyType GetEnemyType(std::string typeString);
	void SpawnEnemy(int currentWave, EEnemyType type, CVector2 pos);
public:
	CLevelLoader(CPlayer* playerRef, std::vector<CProjectile>& enemyBullets, SDL_Renderer* renderer);
	void Load(std::string levelName);
};