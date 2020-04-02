#pragma once
#include "Defines.h"
#include "CVector2.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class CButton
{
private:
	CVector2 mPosition;
	CVector2 mSize;
	SDL_Rect mButtonBox;
	SDL_Surface* mTextSurface;
	SDL_Texture* mTextTexture;
	EButtonAction mButtonAction;
	SDL_Texture* mButtonTexture;
public:
	CButton(CVector2 position, CVector2 size, SDL_Texture* buttonTexture, SDL_Renderer* renderer, EButtonAction buttonAction);
	CButton(CVector2 position, CVector2 size, TTF_Font* font,const char* text, SDL_Color color, SDL_Renderer* renderer, EButtonAction buttonAction);
	bool IsClicked(CVector2 mousePos);
	void Render(SDL_Renderer& renderer);
	EButtonAction GetAction();
};

