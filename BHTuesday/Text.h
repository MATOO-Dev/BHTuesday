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

Text::Text(CVector2 position, CVector2 size, std::string text, SDL_Renderer* renderer, int fontSize, SDL_Color textColor) :
	mPosition(position),
	mSize(size),
	mTextTexture(SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Blended(CAssetManager::CreateSizedFont(fontSize), text.c_str(), textColor)))
{
	mTextBox.h = mSize.y;
	mTextBox.w = mSize.x;
	mTextBox.x = mPosition.x - (mSize.x / 2);
	mTextBox.y = mPosition.y - (mSize.y / 2);
}

Text::~Text()
{
	delete mTextTexture;
}

void Text::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, mTextTexture, NULL, &mTextBox);
}

void Text::UpdateText(std::string text, SDL_Renderer& renderer, int fontSize, SDL_Color textColor)
{
	mTextTexture = SDL_CreateTextureFromSurface(&renderer, TTF_RenderText_Blended(CAssetManager::CreateSizedFont(fontSize), text.c_str(), textColor));
}
