#include "CLevelLoader.h"

void CLevelLoader::Load(std::string levelName)
{
	int waveAmount;
}

void CLevelLoader::ParseFile(std::string fileName)
{
	std::ifstream levelFile;
	levelFile.open("data/level/default/" + fileName);
	if (levelFile.is_open() == false)
	{
		//CGameManager::ThrowErrorMesssage("Level error", "Failed to open level file");
		std::cout << "error, failed to open file" << std::endl;
	}

	//read from file here
	//parse entire file
	//add contents to string array
	//close file
	//set variables based on corresponding array entry
	for (std::string currentLine; std::getline(levelFile, currentLine, ';'); )
	{
		//...for each line in input...
		fileLines.push_back(currentLine);
	}

	for (std::string test : fileLines)
		std::cout << test << std::endl;


	levelFile.close();
}

void CLevelLoader::SpawnEnemy()
{

}