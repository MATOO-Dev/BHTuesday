#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

class CAssetManager
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string filename);
	static SDL_Rect CreateTextureRect(SDL_Texture* texture, float scale);
	static TTF_Font* CreateSizedFont(int size);
};

