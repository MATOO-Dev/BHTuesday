#pragma once

#include "CVector2.h"
#include "CAssetManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

struct Text
{
private:
	CVector2 mPosition;
	CVector2 mSize;
	SDL_Rect mTextBox;
	SDL_Texture* mTextTexture;
public:
	Text(CVector2 position, CVector2 size, std::string text, SDL_Renderer* renderer, int fontSize, SDL_Color textColor);
	~Text();
	void Render(SDL_Renderer& renderer);
	void UpdateText(std::string text, SDL_Renderer& renderer, int fontsize, SDL_Color textColor);
};