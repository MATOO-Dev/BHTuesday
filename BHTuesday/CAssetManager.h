#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class CAssetManager
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string filename);
};

