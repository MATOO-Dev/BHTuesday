#include "CLevelLoader.h"

CLevelLoader::CLevelLoader(CPlayer* playerRef, std::vector<CProjectile>& enemyBullets, SDL_Renderer* renderer) :
	mPlayerRef(playerRef),
	mEnemyBullets(enemyBullets),
	mRenderer(renderer)
{}

CLevelLoader::~CLevelLoader()
{
}

Level CLevelLoader::Load(std::string levelName)
{
	//read file contents
	ParseFile(levelName + ".txt");
	//set variables based on corresponding array entry
	int currentWave = 0;
	loadingLevel = Level();
	EEnemyType eType = EEnemyType::Null;
	int xPos, yPos;
	CVector2 ePos = CVector2(0, 0);

	for (int i = 0; i < fileLines.size(); i++)
	{
		ELevelLoadAction lineAction = GetLoadAction(fileLines[i]);
		switch (lineAction)
		{
		case ELevelLoadAction::SetWaveAmount:
			waveAmount = std::stoi(fileLines[i].substr(11));
			break;
		case ELevelLoadAction::StartWave:
			loadingLevel.mLevelWaves.push_back(Wave());
			break;
		case ELevelLoadAction::SpawnEnemy:
			eType = GetEnemyType(fileLines[i].substr(12));
			xPos = std::stoi(SeperateString(fileLines[i + 1].substr(12), ','));
			yPos = std::stoi(SeperateString(fileLines[i + 1].substr(17), ')'));
			i ++;
			ePos = CVector2(xPos, yPos);
			if (eType != EEnemyType::Null)
				SpawnEnemy(currentWave, eType, ePos);
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

	return loadingLevel;
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

EEnemyType CLevelLoader::GetEnemyType(std::string typeString)
{
	if (typeString.find("Pellets") != std::string::npos)
		return EEnemyType::Pellets;
	if (typeString.find("Kamikaze") != std::string::npos)
		return EEnemyType::Kamikaze;
	return EEnemyType::Null;
}

void CLevelLoader::SpawnEnemy(int currentWave, EEnemyType type, CVector2 pos)
{
	CEnemy* enemyToPush;
	switch (type)
	{
	case EEnemyType::Pellets:
		enemyToPush = new EnemyPellets(pos, CVector2(0, 100), mPlayerRef, &mEnemyBullets, mRenderer);
		break;
	case EEnemyType::Kamikaze:
		enemyToPush = new EnemyKamikaze(pos, CVector2(0, 100), mPlayerRef, &mEnemyBullets, mRenderer);
		break;
	}
	loadingLevel.mLevelWaves[currentWave].mWaveEnemys.push_back(enemyToPush);
}

std::string CLevelLoader::SeperateString(std::string input, char seperator)
{
	std::string output = "";
	for (char x : input)
	{
		if (x == seperator)
		{
			std::cout << output << std::endl;
			return output;
		}
		else
		{
			output = output + x;
		}
	}
	return "error, failed to find seperator";
}