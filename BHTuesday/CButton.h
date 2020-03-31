#pragma once
#include "CVector2.h"
#include <SDL.h>	

class CButton
{
private:
	CVector2 mPosition;
	CVector2 mSize;
	SDL_Rect mButtonBox;
public:
	CButton(CVector2 position, CVector2 size);
	bool IsClicked(CVector2 mousePos);
	void Render(SDL_Renderer* renderer);
	void DoAction();
};

