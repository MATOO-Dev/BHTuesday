#pragma once

#include "Defines.h"
#include "CButton.h"
#include <SDL.h>
#include <vector>

class CMenuManager
{
private:
	SDL_Renderer* mRenderer;
	std::vector<CButton> mMenuButtons;
public:
	CMenuManager();
	void LoadMenu(EMenuType menuType);
	void ClearMenu();
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
	void RenderButtons(SDL_Renderer* renderer);
};

