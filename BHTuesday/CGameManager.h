#pragma once

class CPlayer;
class CEnemy;

#include "CVector2.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "EnemySubclassIncluder.h"
#include "CProjectile.h"
#include "CLevelEditor.h"
#include "CButton.h"
#include "Level.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <string>

class CGameManager
{
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	EGameState mActiveGameState;
	int mPlayerScore;
	int mTotalScore;
	CPlayer* mPlayerRef;
	Level activeLevel;
	std::vector<CEnemy*> mEnemyRef;
	std::vector<CProjectile> mPlayerBullets;
	std::vector<CProjectile> mEnemyBullets;
	std::vector<CButton> mMenuButtons;
	//std::vector<Image> mMenuImages;
	//std::vector<Text> mMenuTexts;
	//std::vector //installed upgrades bool vector
	int Volume; //correct data type?
	TTF_Font* consolasFont;
	bool& mGameRunning;
	void OverrideButtonText(std::vector<std::string> texts);
public:
	CGameManager(bool& running);
	~CGameManager();
	bool InitializeSDL();
	static void ThrowErrorMesssage(const char* errorHeader, const char* errorContent);
	void Update(float timeStep);
	void UpdateAll(float timeStep);
	void RenderAll();
	void ClearGameObjects();
	void InitializeGameState(EGameState menuType);
	void ClearMenu();
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};