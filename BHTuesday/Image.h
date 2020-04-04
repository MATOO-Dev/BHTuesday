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

Image::Image(CVector2 position, CVector2 size, std::string textureName, SDL_Renderer* renderer) :
	mPosition(position),
	mSize(size),
	mTexture(CAssetManager::LoadTexture(renderer, textureName))
{
	mImageBox.h = mSize.y;
	mImageBox.w = mSize.x;
	mImageBox.x = mPosition.x - (mSize.x / 2);
	mImageBox.y = mPosition.y - (mSize.y / 2);
}

Image::~Image()
{
	delete mTexture;
}

void Image::Render(SDL_Renderer& renderer)
{
	if (mTexture != nullptr)
		SDL_RenderCopy(&renderer, mTexture, NULL, &mImageBox);
}