#include "Image.h"

Image::Image(CVector2 position, CVector2 size, std::string textureName, SDL_Renderer* renderer) :
	mPosition(position),
	mSize(size),
	mTexture(CAssetManager::LoadTexture(renderer, textureName))
{
	mImageBox.h = (int)mSize.y;
	mImageBox.w = (int)mSize.x;
	mImageBox.x = (int)mPosition.x - ((int)mSize.x / 2);
	mImageBox.y = (int)mPosition.y - ((int)mSize.y / 2);
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);
}

void Image::Render(SDL_Renderer& renderer)
{
	if (mTexture != nullptr)
		SDL_RenderCopy(&renderer, mTexture, NULL, &mImageBox);
}