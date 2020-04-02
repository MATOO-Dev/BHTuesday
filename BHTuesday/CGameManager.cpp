#include "CGameManager.h"

CGameManager::CGameManager() :
	mActiveGameState(EGameState::MainMenu),
	mWindow(nullptr),
	mRenderer(nullptr),
	consolasFont(nullptr),
	mMenuButtons()
{}

bool CGameManager::InitializeSDL()
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

	consolasFont = CreateSizedFont(50);
	if (consolasFont != nullptr)
		//mMenuButtons.push_back(CButton(CVector2(300, 500), CVector2(200, 100), consolasFont, "test", white, mRenderer, EButtonAction::OpenEditorMenu));
		return true;
}

void CGameManager::ThrowErrorMesssage(const char* errorHeader, const char* errorContent)
{
	MessageBoxA(NULL, errorContent, errorHeader, MB_OK);
}

void CGameManager::Update()
{
	switch (mActiveGameState)
	{
	case EGameState::MainMenu:
		//update + render buttons
		RenderAll();
		break;
	case EGameState::Active:
		UpdateAll();
		RenderAll();
		break;
	case EGameState::PauseMenu:
		//like active, but without update and with menu options
		RenderAll();
		break;
	case EGameState::SettingsMenu:
		//like pause, but without background
		break;
	case EGameState::EditorMenu:
		//level editor
		break;
	case EGameState::UpgradesMenu:
		//upgrade shop
		break;
	default:
		break;
	}
}

void CGameManager::UpdateAll()
{
	/*
	if (mPlayerRef != nullptr)
		mPlayerRef->Update();

	for (CEnemy enemy : mEnemyRef)
		enemy.Update();

	for (CProjectile playerProjectile : mPlayerBullets)
		playerProjectile.Update();

	for (CProjectile enemyProjectile : mEnemyBullets)
		enemyProjectile.Update();
		*/
}

void CGameManager::RenderAll()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	if (mPlayerRef != nullptr)
		mPlayerRef->Render(*mRenderer);

	for (CEnemy enemy : mEnemyRef)
		enemy.Render(*mRenderer);

	for (CProjectile playerProjectile : mPlayerBullets)
		playerProjectile.Render(*mRenderer);

	for (CProjectile enemyProjectile : mEnemyBullets)
		enemyProjectile.Render(*mRenderer);

	for (CButton button : mMenuButtons)
		button.Render(*mRenderer);
	SDL_RenderPresent(mRenderer);
}

void CGameManager::ClearGameObjects()
{
	mPlayerRef = nullptr;
	mEnemyRef.clear();
	mPlayerBullets.clear();
	mEnemyBullets.clear();
}

TTF_Font* CGameManager::CreateSizedFont(int size)
{
	return TTF_OpenFont("data/fonts/consolas.ttf", size);
}

void CGameManager::InitializeMenu(EGameState menuType)
{
	ClearMenu();
	SDL_Color white = { 255, 255, 255 };
	SDL_Color black = { 0, 0, 0 };

	switch (menuType)
	{
	case EGameState::MainMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 370), CVector2(200, 100), consolasFont, "Play", white, mRenderer, EButtonAction::OpenLevelSelectMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 540), CVector2(200, 100), consolasFont, "Settings", white, mRenderer, EButtonAction::OpenSettingsMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 710), CVector2(200, 100), consolasFont, "Editor", white, mRenderer, EButtonAction::OpenEditorMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Upgrades", white, mRenderer, EButtonAction::OpenUpgradesMenu));
		break;
	case EGameState::LevelSelectMenu:
		break;
	case EGameState::Active:
		//no menu
		//maybe hud?
		break;
	case EGameState::PauseMenu:
		break;
	case EGameState::SettingsMenu:
		break;
	case EGameState::EditorMenu:
		break;
	case EGameState::UpgradesMenu:
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
	if (mouseDownEvent.button == SDL_BUTTON_LEFT)
	{
		CVector2 mousePos = CVector2(mouseDownEvent.x, mouseDownEvent.y);
		//mouseDownEvent.button
		for (int i = 0; i < mMenuButtons.size(); i++)
		{
			if (mMenuButtons[i].IsClicked(mousePos))
			{
				switch (mMenuButtons[i].GetAction())
				{
				case EButtonAction::OpenMainMenu:
					InitializeMenu(EGameState::MainMenu);
					break;
				case EButtonAction::OpenLevelSelectMenu:
					InitializeMenu(EGameState::LevelSelectMenu);
					break;
				case EButtonAction::OpenStartGame:
					mMenuButtons.clear();
					//load level here;
					SwitchGameState(EGameState::Active);
					break;
				case EButtonAction::OpenPauseMenu:
					InitializeMenu(EGameState::PauseMenu);
					break;
				case EButtonAction::OpenSettingsMenu:
					InitializeMenu(EGameState::SettingsMenu);
					break;
				case EButtonAction::OpenEditorMenu:
					InitializeMenu(EGameState::EditorMenu);
					break;
				case EButtonAction::OpenUpgradesMenu:
					InitializeMenu(EGameState::UpgradesMenu);
					break;
					//more actions
				default:
					break;
				}
				break;
			}
		}
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
	mActiveGameState = newGameState;
}

void CGameManager::ExitGame()		//replace with bool return on update, instead use this to shutdown sdl, window, renderers, and call destructors from here
{
	ClearGameObjects();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_Quit();
	SDL_Quit();
}