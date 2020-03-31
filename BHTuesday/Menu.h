/*
#pragma once

#include "Defines.h"
#include "CButton.h"
#include <vector>

struct Menu
{
	std::vector<CButton> mMenuButtons;
	void UpdateButtons(SDL_MouseButtonEvent mouseDownEvent);
};

void Menu::UpdateButtons(SDL_MouseButtonEvent mouseDownEvent)		//enter mouse down event
{
	CVector2 mousePos = CVector2(mouseDownEvent.x, mouseDownEvent.y);
	//mouseDownEvent.button
	for (int i = 0; i < mMenuButtons.size(); i++)
	{
		if (mMenuButtons[i].IsClicked(mousePos))
			mMenuButtons[i].DoAction();
	}
}
*/