#pragma once
#include "CPlayer.h"
#include "CEnemy.h"
#include "CLevelEditor.h"
#include <SDL.h>
#include <vector>

class CGameManager
{
private:
	CPlayer* mPlayerRef;
	std::vector<CEnemy*> mEnemyRef;
	//add bullet vectors
	int mPlayerScore;
	//std::vector //installed upgrades bool vector
public:
	CGameManager();
	void Update();
	void UpdateAll();
	void RenderAll();
	void OpenMenu(EMenuType menuToOpen);
	bool SaveSettings();		//bool used for error checks
	bool LoadSettings();		//""
	void SwitchGameState(EGameState newGameState);
	void ExitGame();
};