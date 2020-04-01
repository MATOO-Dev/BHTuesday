#include "CButton.h"

CButton::CButton(CVector2 position, CVector2 size, TTF_Font* font, const char* text, SDL_Color color, SDL_Renderer* renderer) :
	mPosition(position),
	mSize(size),
	mTextSurface(TTF_RenderText_Blended(font, text, color)),
	mTextTexture(SDL_CreateTextureFromSurface(renderer, mTextSurface))
{
	mButtonBox.h = mSize.y;
	mButtonBox.w = mSize.x;
	mButtonBox.x = mPosition.x - (mSize.x / 2);
	mButtonBox.y = mPosition.y - (mSize.y / 2);
}

bool CButton::IsClicked(CVector2 mousePos)
{
	if (mousePos.x > mPosition.x - (mSize.x / 2))
		if (mousePos.x < mPosition.x + (mSize.x / 2))
			if (mousePos.y > mPosition.y - (mSize.y / 2))
				if (mousePos.y < mPosition.y + (mSize.y / 2))
					return true;
	return false;
}

void CButton::Render(SDL_Renderer& renderer)
{
	SDL_RenderDrawRect(&renderer, &mButtonBox);
	SDL_RenderCopy(&renderer, mTextTexture, NULL, &mButtonBox);
}

void CButton::DoAction()
{

}