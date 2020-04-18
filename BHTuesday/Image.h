#pragma once

#include "CVector2.h"
#include "CAssetManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

struct Image
{

private:
	CVector2 mPosition;
	CVector2 mSize;
	SDL_Rect mImageBox;
	SDL_Texture* mTexture;
public:
	Image(CVector2 position, CVector2 size, std::string textureName, SDL_Renderer* renderer);
	~Image();
	void Render(SDL_Renderer& renderer);
};