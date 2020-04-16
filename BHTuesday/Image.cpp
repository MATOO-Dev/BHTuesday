#include "Image.h"

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
	SDL_DestroyTexture(mTexture);
}

void Image::Render(SDL_Renderer& renderer)
{
	if (mTexture != nullptr)
		SDL_RenderCopy(&renderer, mTexture, NULL, &mImageBox);
}