#include "CAssetManager.h"


SDL_Texture* CAssetManager::LoadTexture(SDL_Renderer* renderer, std::string filename)
{
	std::string filepath = "data/textures/" + filename;
	SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str());
	return texture;
}