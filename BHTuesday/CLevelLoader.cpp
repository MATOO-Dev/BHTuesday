#include "CLevelLoader.h"

void CLevelLoader::Load(std::string levelName)
{
	//read file contents
	ParseFile(levelName + ".txt");
	//set variables based on corresponding array entry
	int currentWave = 0;
	loadingLevel = Level();
	CVector2 tempVector = CVector2(0, 0);

	for (std::string currentLine : fileLines)
	{
		std::cout << currentLine << std::endl;
		ELevelLoadAction lineAction = GetLoadAction(currentLine);
		switch (lineAction)
		{
		case ELevelLoadAction::SetWaveAmount:
			waveAmount = std::stoi(currentLine.substr(11, 1));
			break;
		case ELevelLoadAction::StartWave:
			loadingLevel.mLevelWaves.push_back(Wave());
			break;
		case ELevelLoadAction::SpawnEnemy:
			std::cout << currentLine.length() << std::endl;
			break;
		case ELevelLoadAction::EndWave:
			currentWave++;
			break;
		case ELevelLoadAction::EndLevel:
			std::cout << "finished loading level" << std::endl;
			break;
		default:
			break;
		}
	}
}

void CLevelLoader::ParseFile(std::string fileName)
{
	std::vector<std::string>().swap(fileLines);
	std::ifstream levelFile;
	levelFile.open("data/level/default/" + fileName);
	if (levelFile.is_open() == false)
	{
		//CGameManager::ThrowErrorMesssage("Level loading error", "Failed to open level file");
		std::cout << "error, failed to open file" << std::endl;
	}

	//parse entire file
	//add contents to string array
	for (std::string currentLine; std::getline(levelFile, currentLine);)
	{
		fileLines.push_back(currentLine);
	}

	//close file
	levelFile.close();
}

ELevelLoadAction CLevelLoader::GetLoadAction(std::string lineContent)
{
	if (lineContent.find("waveAmount") != std::string::npos)
		return ELevelLoadAction::SetWaveAmount;
	if (lineContent.find("startWave") != std::string::npos)
		return ELevelLoadAction::StartWave;
	if (lineContent.find("enemyType") != std::string::npos)
		return ELevelLoadAction::SpawnEnemy;
	if (lineContent.find("endWave") != std::string::npos)
		return ELevelLoadAction::EndWave;
	if (lineContent.find("endLevel") != std::string::npos)
		return ELevelLoadAction::EndLevel;
}

void CLevelLoader::SpawnEnemy()
{

}