#pragma once

#include "Defines.h"
#include "Level.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class CLevelLoader
{
private:
	int waveAmount;
	Level loadingLevel;
	std::vector<std::string> fileLines;
	void SpawnEnemy();
	void ParseFile(std::string fileName);
	ELevelLoadAction GetLoadAction(std::string lineContent);
public:
	void Load(std::string levelName);
};