#include "Text.h"

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
	SDL_DestroyTexture(mTextTexture);
}

void Text::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, mTextTexture, NULL, &mTextBox);
}

void Text::UpdateText(std::string text, SDL_Renderer& renderer, int fontSize, SDL_Color textColor)
{
	mTextTexture = SDL_CreateTextureFromSurface(&renderer, TTF_RenderText_Blended(CAssetManager::CreateSizedFont(fontSize), text.c_str(), textColor));
}
