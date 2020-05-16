#include "CGameManager.h"

CGameManager::CGameManager(bool& running) :
	mActiveGameState(EGameState::MainMenu),
	mWindow(nullptr),
	mPlayerRef(nullptr),
	mRenderer(nullptr),
	consolasFont(nullptr),
	mMenuButtons(),
	mGameRunning(running),
	mPlayerScore(0),
	mTotalScore(0),
	Volume(0)
{}

CGameManager::~CGameManager()
{
	delete mPlayerRef;
	mEnemyRef.clear();
}

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
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		ThrowErrorMesssage("Critical error", "Failed to Initialize PNG support");
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

	consolasFont = CAssetManager::CreateSizedFont(100);
	return true;
}

void CGameManager::ThrowErrorMesssage(const char* errorHeader, const char* errorContent)
{
	MessageBoxA(NULL, errorContent, errorHeader, MB_OK);
}

void CGameManager::Update(float timeStep)
{

	switch (mActiveGameState)
	{
	case EGameState::MainMenu:
		//update + render buttons
		UpdateAll(timeStep);
		OverrideButtonText({ "Play", "Settings", "Editor", "Upgrades", "Quit" });
		break;
	case EGameState::LevelSelectMenu:
		OverrideButtonText({ "Level 1", "Level 2", "Level 3", "Menu" });
		UpdateAll(timeStep);
		break;
	case EGameState::Active:
		UpdateAll(timeStep);
		OverrideButtonText({ ("Score: " + std::to_string(mPlayerScore)).c_str(), ("Health: " + std::to_string(int(mPlayerRef->GetHealth()))).c_str() });
		if (mEnemyRef.size() == 0)
		{
			if (mActiveWaveIndex + 1 != mActiveLevel.mLevelWaves.size())
			{
				mActiveWaveIndex++;
				QueueWave();
			}
			else if (mActiveWaveIndex + 1 == mActiveLevel.mLevelWaves.size())
				InitializeGameState(EGameState::VictoryMenu);
		}
		break;
	case EGameState::PauseMenu:
		//like active, but without update and with menu options
		OverrideButtonText({ "Level 1", "Level 2", "Level 3", "Menu" });
		break;
	case EGameState::SettingsMenu:
		//like pause, but without background objects
		OverrideButtonText({ "Video", "Volume", "-", "+", "Menu" });
		break;
	case EGameState::EditorMenu:
		//level editor
		OverrideButtonText({ "Menu" });
		break;
	case EGameState::UpgradesMenu:
		//upgrade shop
		OverrideButtonText({ "Menu" });
		break;
	case EGameState::DeathMenu:
		OverrideButtonText({ "You Died", "Menu" });
		break;
	case EGameState::VictoryMenu:
		OverrideButtonText({ "You Win", "Menu" });
		break;
	default:
		break;
	}
	RenderAll();
}

void CGameManager::UpdateAll(float timeStep)		//updates all gameobjects, excluding buttons
{
	EControlStyle controlStyle = EControlStyle::Keyboard;
	if (mPlayerRef != nullptr)
	{
		mPlayerRef->Update(timeStep, controlStyle);
		if (mPlayerRef->GetHealth() < 0)
		{
			//mPlayerRef = nullptr;
			InitializeGameState(EGameState::DeathMenu);
		}
	}

	for (CEnemy* enemy : mEnemyRef)
	{
		enemy->Update(timeStep);
		if (enemy->GetHealth() < 0)
			int x = 5;
	}

	//update projectiles and remove if out of bounds
	std::vector<CProjectile>::iterator it = mPlayerBullets.begin();
	while (it != mPlayerBullets.end())
		if (it->Update(timeStep) == false)
			it = mPlayerBullets.erase(it);
		else
			it++;

	//also check against enemy collision
	for (size_t i = 0; i < mEnemyRef.size(); i++)
	{
		it = mPlayerBullets.begin();
		while (it != mPlayerBullets.end())
			if (mEnemyRef[i] != nullptr && it->EnemyCollision(*mEnemyRef[i]) == true)
			{
				it = mPlayerBullets.erase(it);

				if (mEnemyRef[i]->GetHealth() < 0)
				{
					mEnemyRef[i] = nullptr;
					mPlayerScore++;
				}
			}
			else
				it++;

		//should remove enemy if it collides with player
		if (mEnemyRef[i] != nullptr && mEnemyRef[i]->IntersectsPlayer())
			mEnemyRef[i] = nullptr;
		if (mEnemyRef[i] != nullptr && mEnemyRef[i]->OutOfBounds() && mEnemyRef[i]->GetState() != EEnemyState::Intro)
		{
			mEnemyRef[i] = nullptr;
		}
	}

	//remove killed enemys
	mEnemyRef.erase(std::remove(mEnemyRef.begin(), mEnemyRef.end(), nullptr), mEnemyRef.end());

	//same as previous 2, but inverted
	it = mEnemyBullets.begin();
	while (it != mEnemyBullets.end())
		if (it->Update(timeStep) == false || it->PlayerCollision(*mPlayerRef) == true)	//C6011 is irrelevant because projectiles can only exist while mPlayerRef is not null, 
			it = mEnemyBullets.erase(it);												//so mPlayerRef cannot be nullptr in this case
		else
			it++;
}

void CGameManager::RenderAll()		//renders all gameobjects, including buttons
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	if (mPlayerRef != nullptr)
		mPlayerRef->Render();

	for (CEnemy* enemy : mEnemyRef)
		enemy->Render();

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
	std::vector<CEnemy*>().swap(mEnemyRef);
	mEnemyRef.shrink_to_fit();
	std::vector<CProjectile>().swap(mPlayerBullets);
	mPlayerBullets.shrink_to_fit();
	std::vector<CProjectile>().swap(mEnemyBullets);
	mEnemyBullets.shrink_to_fit();
}

void CGameManager::InitializeGameState(EGameState menuType)
{
	ClearMenu();
	if (menuType != EGameState::PauseMenu && menuType != EGameState::DeathMenu)
		ClearGameObjects();
	SDL_Color white = { 255, 255, 255 };
	SDL_Color black = { 0, 0, 0 };

	switch (menuType)
	{
	case EGameState::MainMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 200), CVector2(200, 100), consolasFont, "Play", white, mRenderer, EButtonAction::OpenLevelSelectMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 370), CVector2(200, 100), consolasFont, "Settings", white, mRenderer, EButtonAction::OpenSettingsMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 540), CVector2(200, 100), consolasFont, "Editor", white, mRenderer, EButtonAction::OpenEditorMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 710), CVector2(200, 100), consolasFont, "Upgrades", white, mRenderer, EButtonAction::OpenUpgradesMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Quit", white, mRenderer, EButtonAction::QuitGame));
		break;
	case EGameState::LevelSelectMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 200), CVector2(200, 100), consolasFont, "Level 1", white, mRenderer, EButtonAction::StartGame));
		mMenuButtons.push_back(CButton(CVector2(300, 370), CVector2(200, 100), consolasFont, "Level 2", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 540), CVector2(200, 100), consolasFont, "Level 3", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::Active:
		if (mActiveGameState != EGameState::PauseMenu)
		{
			mPlayerScore = 0;
			mMenuButtons.push_back(CButton(CVector2(75, 975), CVector2(150, 50), consolasFont, "Score: 0", white, mRenderer, EButtonAction::None));
			mMenuButtons.push_back(CButton(CVector2(525, 975), CVector2(150, 50), consolasFont, "Health: 0", white, mRenderer, EButtonAction::None));
			mPlayerRef = new CPlayer(CVector2(300, 750), mPlayerBullets, mRenderer, "PlayerTexture.png");
			//old system (manual spawning)
			for (int i = 0; i < 6; i++)
				mEnemyRef.push_back(new EnemyPellets(CVector2(float(100 * i + 50), 200), CVector2(0, 200), mPlayerRef, &mEnemyBullets, mRenderer));
			mEnemyRef.push_back(new EnemyKamikaze(CVector2(300, 400), CVector2(0, 100), mPlayerRef, &mEnemyBullets, mRenderer));

			//new system (loading from file)
			CLevelLoader levelLoader = CLevelLoader(mPlayerRef, mEnemyBullets, mRenderer);
			mActiveLevel = levelLoader.Load("testFile");
			mActiveWaveIndex = 0;
			QueueWave();
		}
		//300, 250
		//maybe hud?
		break;
	case EGameState::PauseMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 370), CVector2(200, 100), consolasFont, "Resume", white, mRenderer, EButtonAction::StartGame));
		mMenuButtons.push_back(CButton(CVector2(300, 710), CVector2(200, 100), consolasFont, "Editor", white, mRenderer, EButtonAction::OpenEditorMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 540), CVector2(200, 100), consolasFont, "Settings", white, mRenderer, EButtonAction::OpenSettingsMenu));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::SettingsMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 540), CVector2(200, 100), consolasFont, "Video", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 710), CVector2(200, 100), consolasFont, "Volume", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(100, 710), CVector2(60, 100), consolasFont, "-", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(500, 710), CVector2(60, 100), consolasFont, "+", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::EditorMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::UpgradesMenu:
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::DeathMenu:
		mTotalScore += mPlayerScore;
		mMenuButtons.push_back(CButton(CVector2(300, 50), CVector2(300, 100), consolasFont, "You Died", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	case EGameState::VictoryMenu:
		mTotalScore += mPlayerScore;
		mMenuButtons.push_back(CButton(CVector2(300, 50), CVector2(300, 100), consolasFont, "You Win", white, mRenderer, EButtonAction::None));
		mMenuButtons.push_back(CButton(CVector2(300, 880), CVector2(200, 100), consolasFont, "Menu", white, mRenderer, EButtonAction::OpenMainMenu));
		break;
	default:
		break;
	}
	SwitchGameState(menuType);
}

void CGameManager::ClearMenu()
{
	std::vector<CButton>().swap(mMenuButtons);
	mMenuButtons.shrink_to_fit();
}

void CGameManager::UpdateButtons(SDL_MouseButtonEvent mouseDownEvent)		//enter mouse down event
{
	if (mouseDownEvent.button == SDL_BUTTON_LEFT)
	{
		CVector2 mousePos = CVector2((float)mouseDownEvent.x, (float)mouseDownEvent.y);
		//mouseDownEvent.button
		for (size_t i = 0; i < mMenuButtons.size(); i++)
		{
			if (mMenuButtons[i].IsClicked(mousePos))
			{
				switch (mMenuButtons[i].GetAction())
				{
				case EButtonAction::OpenMainMenu:
					InitializeGameState(EGameState::MainMenu);
					break;
				case EButtonAction::OpenLevelSelectMenu:
					InitializeGameState(EGameState::LevelSelectMenu);
					break;
				case EButtonAction::StartGame:
					mMenuButtons.clear();
					//load level here;
					InitializeGameState(EGameState::Active);
					break;
				case EButtonAction::OpenPauseMenu:
					InitializeGameState(EGameState::PauseMenu);
					break;
				case EButtonAction::OpenSettingsMenu:
					InitializeGameState(EGameState::SettingsMenu);
					break;
				case EButtonAction::OpenEditorMenu:
					InitializeGameState(EGameState::EditorMenu);
					break;
				case EButtonAction::OpenUpgradesMenu:
					InitializeGameState(EGameState::UpgradesMenu);
					break;
				case EButtonAction::QuitGame:
					//bool* tempBool = false;
					mGameRunning = false;
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
	ClearMenu();
	ClearGameObjects();
	TTF_CloseFont(consolasFont);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void CGameManager::OverrideButtonText(std::vector<std::string> texts)
{
	for (size_t i = 0; i < texts.size(); i++)
	{
		if (mMenuButtons.size() >= i + 1)
			mMenuButtons[i].UpdateText(consolasFont, texts[i].c_str(), white, mRenderer);
	}
}

void CGameManager::QueueWave()
{
	mEnemyRef = mActiveLevel.mLevelWaves[mActiveWaveIndex].mWaveEnemys;
	//updating once to prevent enemy appearing in upper left corner when loading in
	for (CEnemy* eCurrent : mEnemyRef)
		eCurrent->Update(0.016);
}