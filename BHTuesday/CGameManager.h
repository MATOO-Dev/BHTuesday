#pragma once
#include "CVector2.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CProjectile.h"
#include "CLevelEditor.h"
#include "CButton.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <Windows.h>
#include <fstream>
#include <algorithm>

class CGameManager
{
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	EGameState mActiveGameState;
	int mPlayerScore;
	CPlayer* mPlayerRef;
	std::vector<CEnemy> mEnemyRef;
	std::vector<CProjectile> mPlayerBullets;
	std::vector<CProjectile> mEnemyBullets;
	std::vector<CButton> mMenuButtons;
	//std::vector //installed upgrades bool vector
	int Volume; //correct data type?
	TTF_Font* consolasFont;
public:
	CGameManager();
	bool InitializeSDL();
	void ThrowErrorMesssage(const char* errorHeader, const char* errorContent);
	void Update(float timeStep);
	void UpdateAll(float timeStep);
	void RenderAll();
	void ClearGameObjects();
	TTF_Font* CreateSizedFont(int size);
	void RemoveFromVector();
	void InitializeGameState(EGameState menuType);
	void ClearMenu();
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};