#pragma once
#include "CVector2.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CLevelEditor.h"
#include "CMenuManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <Windows.h>
#include <fstream>

class CGameManager
{
private:
	CPlayer* mPlayerRef;
	std::vector<CEnemy*> mEnemyRef;
	//add bullet vectors
	int mPlayerScore;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	//std::vector //installed upgrades bool vector
	int Volume; //correct data type?
	TTF_Font* consolasFont;
	std::vector<CButton> mMenuButtons;
public:
	CGameManager();
	bool InitializeSDL(SDL_Renderer* renderer);
	void ThrowErrorMesssage(const char* errorHeader, const char* errorContent);
	void Update();
	void UpdateAll();
	void RenderAll(SDL_Renderer* renderer);
	void ClearGameObjects();
	TTF_Font* CreateSizedFont(int size);
	void InitializeMenu(EMenuType menuType);
	void ClearMenu();
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
	void RenderButtons(SDL_Renderer* renderer);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};