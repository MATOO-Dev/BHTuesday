#pragma once
#include "CVector2.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CProjectile.h"
#include "CLevelEditor.h"
#include "CButton.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <Windows.h>
#include <fstream>

class CGameManager
{
private:
	EGameState mActiveGameState;
	CPlayer* mPlayerRef;
	std::vector<CEnemy> mEnemyRef;
	std::vector<CProjectile> mEnemyBullets;
	std::vector<CProjectile> mPlayerBullets;
	int mPlayerScore;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	//std::vector //installed upgrades bool vector
	int Volume; //correct data type?
	TTF_Font* consolasFont;
	std::vector<CButton> mMenuButtons;
public:
	CGameManager();
	bool InitializeSDL();
	void ThrowErrorMesssage(const char* errorHeader, const char* errorContent);
	void Update(float timeStep);
	void UpdateAll(float timeStep);
	void RenderAll();
	void ClearGameObjects();
	TTF_Font* CreateSizedFont(int size);
	void InitializeGameState(EGameState menuType);
	void ClearMenu();
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};