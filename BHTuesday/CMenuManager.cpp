#include "CMenuManager.h"

/*
CMenuManager():
    mRenderer(renderer)
{}
*/

void CMenuManager::LoadMenu(EMenuType menuType)
{
	switch (menuType)
	{
    case EMenuType::MainMenu:
        //mMenuButtons.push_back(CButton(CVector2(300, 500), CVector2(100, 50)));
        break;
    case EMenuType::Paused:
        break;
    case EMenuType::Settings:
        break;
    case EMenuType::Editor:
        break;
    case EMenuType::Upgrades:
        break;
    default:
        break;
	}
}

void CMenuManager::ClearMenu()
{
    mMenuButtons.clear();
}

void CMenuManager::UpdateButtons(SDL_MouseButtonEvent mouseDownEvent)		//enter mouse down event
{
    CVector2 mousePos = CVector2(mouseDownEvent.x, mouseDownEvent.y);
    //mouseDownEvent.button
    for (int i = 0; i < mMenuButtons.size(); i++)
    {
        if (mMenuButtons[i].IsClicked(mousePos))
            mMenuButtons[i].DoAction();
    }
}

void CMenuManager::RenderButtons(SDL_Renderer* renderer) 
{
    for (int i = 0; i < mMenuButtons.size(); i++)
    {
        mMenuButtons[i].Render(renderer);
    }
}