#include "CAssetManager.h"


SDL_Texture* CAssetManager::LoadTexture(SDL_Renderer* renderer, std::string filename)
{
	std::string filepath = "data/textures/" + filename;
	SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str());
	return texture;
}

SDL_Rect CAssetManager::CreateTextureRect(SDL_Texture* texture, float scale)
{
	int width;
	int height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	return SDL_Rect{ 0, 0, int(width * scale), int(height * scale)};
}

TTF_Font* CAssetManager::CreateSizedFont(int size)
{
	return TTF_OpenFont("data/fonts/consolas.ttf", size);
}