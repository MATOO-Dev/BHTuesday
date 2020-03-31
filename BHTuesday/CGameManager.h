#pragma once
#include "CPlayer.h"
#include "CEnemy.h"
#include "CLevelEditor.h"
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
	//std::vector //installed upgrades bool vector
	int Volume; //correct data type?
public:
	CGameManager();
	bool InitializeSDL();
	void ThrowErrorMesssage(const char* errorHeader, const char* errorContent);
	void Update();
	void UpdateAll();
	void RenderAll();
	void ClearGameObjects();
	void ClearMenus();
	void OpenMenu(EMenuType menuToOpen);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};