#include "CGameManager.h"

CGameManager::CGameManager()
{}

void CGameManager::Update()
{

}

void CGameManager::UpdateAll()
{

}

void CGameManager::RenderAll()
{

}

void CGameManager::ClearGameObjects()
{

}

void CGameManager::ClearMenus()
{

}

void CGameManager::OpenMenu(EMenuType menuToOpen)
{

}

bool CGameManager::SaveSettings()		//bool used for error checks
{
	std::ofstream settingsFile;
	settingsFile.open("data/configs/settings.txt", std::ofstream::trunc);
	if (settingsFile.is_open() == false)
	{
		std::cout << "error, unable to open settings file";
		return false;
	}

	//write to file here, example below
	//settingsFile << setting << std::endl;

	settingsFile.close();
	return true;
}

bool CGameManager::LoadSettings()		//bool used for error checks
{
	std::ifstream settingsFile;
	settingsFile.open("data/configs/settings.txt");
	if (settingsFile.is_open() == false)
	{
		std::cout << "error, unable to open settings file";
		return false;
	}

	//read from file here
	//create string array of settings
	//parse entire file
	//close file
	//set variables based on corresponding array entry

	settingsFile.close();
	return true;
}

void CGameManager::SwitchGameState(EGameState newGameState)
{
	
}

void CGameManager::ExitGame()
{

}