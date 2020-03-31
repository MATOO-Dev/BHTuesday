#include "CGameManager.h"

CGameManager::CGameManager() :
	mWindow(nullptr),
	mRenderer(nullptr),
	consolasFont(nullptr),
	mMenuButtons()
{}

bool CGameManager::InitializeSDL(SDL_Renderer* renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ThrowErrorMesssage("Critical error", "Failed to Initialize SDL2_Video");
		return false;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		ThrowErrorMesssage("Critical error", "Failed to Initialize SDL2_Audio");
		return false;
	}
	if (TTF_Init() < 0)
	{
		ThrowErrorMesssage("Critical error", "Failed to Initialize SDL2_TTF");
		return false;
	}
	if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &mWindow, &mRenderer) < 0)
	{
		ThrowErrorMesssage("Critical error", "Failed to Create Window or Renderer");
		return false;
	}

	SDL_Color white = { 255, 255, 255 };
	SDL_Color black = { 0, 0, 0 };

	consolasFont = CreateSizedFont(50);
	if (consolasFont != nullptr)
		mMenuButtons.push_back(CButton(CVector2(300, 500), CVector2(200, 100), consolasFont, "test", white, renderer));

	return true;
}

void CGameManager::ThrowErrorMesssage(const char* errorHeader, const char* errorContent)
{
	MessageBoxA(NULL, errorContent, errorHeader, MB_OK);
}

void CGameManager::Update()
{

}

void CGameManager::UpdateAll()
{

}

void CGameManager::RenderAll(SDL_Renderer* renderer)
{
	for (int i = 0; i < mMenuButtons.size(); i++)
	{
		mMenuButtons[i].Render(renderer);
	}
}

void CGameManager::ClearGameObjects()
{

}

TTF_Font* CGameManager::CreateSizedFont(int size)
{
	return TTF_OpenFont("data/fonts/consolas.ttf", size);
}

void CGameManager::InitializeMenu(EMenuType menuType)
{
	switch (menuType)
	{
	case EMenuType::MainMenu:
		//mMenuButtons.push_back(CButton(CVector2(300, 500), CVector2(100, 50)));
		break;
	case EMenuType::Paused:
		break;
	case EMenuType::Settings:
		break;
	case EMenuType::Editor:
		break;
	case EMenuType::Upgrades:
		break;
	default:
		break;
	}
}

void CGameManager::ClearMenu()
{
	mMenuButtons.clear();
}

void CGameManager::UpdateButtons(SDL_MouseButtonEvent mouseDownEvent)		//enter mouse down event
{
	CVector2 mousePos = CVector2(mouseDownEvent.x, mouseDownEvent.y);
	//mouseDownEvent.button
	for (int i = 0; i < mMenuButtons.size(); i++)
	{
		if (mMenuButtons[i].IsClicked(mousePos))
			mMenuButtons[i].DoAction();
	}
}

void CGameManager::RenderButtons(SDL_Renderer* renderer)
{
	for (int i = 0; i < mMenuButtons.size(); i++)
	{
		mMenuButtons[i].Render(renderer);
	}
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
	//mActiveGameState = newGameState
}

void CGameManager::ExitGame()		//replace with bool return on update, instead use this to shutdown sdl, window, renderers, and call destructors from here
{

}