// BHTuesday.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <SDL.h>
#include <vector>
#include "CPlayer.h"
#include "CEnemy.h"
#include "Defines.h"

#define TICK_INTERVAL 16


int main(int argc, char* argv[])
{
	//initialize variables
	static CPlayer* myPlayer = new CPlayer(CVector2(300, 875));
	static EControlStyle myControlStyle = EControlStyle::Keyboard;
	static EGameState activeGameState = EGameState::Active;
	static ETheme activeTheme = ETheme::Light;
	std::vector<CEnemy> Enemys;

	Enemys.push_back(CEnemy(CVector2(100, 100), myPlayer));
	Enemys.push_back(CEnemy(CVector2(200, 100), myPlayer));
	Enemys.push_back(CEnemy(CVector2(300, 100), myPlayer));
	Enemys.push_back(CEnemy(CVector2(400, 100), myPlayer));

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* Window = NULL;
		SDL_Renderer* Renderer = NULL;

		//create a window using sdl
		if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &Window, &Renderer) == 0)
		{
			SDL_bool completed = SDL_FALSE;

			//game loop
			while (!completed)
			{
				int before = SDL_GetTicks();
				SDL_Event event;

				//manages background and foreground color in regards to active theme
				switch (activeTheme)
				{
				case(ETheme::Light):
					SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(Renderer);
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					break;
				case(ETheme::Dark):
					SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(Renderer);
					SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					break;
				}

				{
					//orientation lines, will be removed later
					SDL_SetRenderDrawColor(Renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawLine(Renderer, 0, 0, 600, 1000);
					SDL_RenderDrawLine(Renderer, 600, 0, 0, 1000);
					SDL_RenderDrawLine(Renderer, 300, 0, 300, 1000);
					SDL_RenderDrawLine(Renderer, 0, 250, 600, 250);
					SDL_RenderDrawLine(Renderer, 0, 500, 600, 500);
					SDL_RenderDrawLine(Renderer, 0, 750, 600, 750);
					SDL_SetRenderDrawColor(Renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawLine(Renderer, myPlayer->GetPosition().x, myPlayer->GetPosition().y, 300, 500);
					SDL_SetRenderDrawColor(Renderer, 255, 25 < 5, 255, SDL_ALPHA_OPAQUE);
				}

				//manages current Game State
				switch (activeGameState)
				{
				case(EGameState::Menu):
					break;
				case(EGameState::Active):
					myPlayer->Update((float)TICK_INTERVAL / 1000.f, myControlStyle);
					myPlayer->Render(*Renderer);
					for (int i = 0; i < Enemys.size(); i++)
					{
						Enemys[i].Update((float)TICK_INTERVAL / 1000.f);
						Enemys[i].Render(*Renderer);
					}
					break;
				case(EGameState::Paused):
					myPlayer->Render(*Renderer);
					for (int i = 0; i < Enemys.size(); i++)
					{
						Enemys[i].Render(*Renderer);
					}
					break;
				case(EGameState::Settings):
					break;
				}

				//displays the rendered image
				SDL_RenderPresent(Renderer);

				{
					//ensures tickspeed is stable(?)
					int after = SDL_GetTicks();
					int ticks = after - before;
					if (ticks < 16)
					{
						SDL_Delay(16 - ticks);
					}

					ticks = SDL_GetTicks() - before;
				}

				{
					//exits the Game loop upon the event SDL_QUIT occuring
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_QUIT) {
							completed = SDL_TRUE;
						}
					}
				}

			}
		}
		if (Renderer)
			SDL_DestroyRenderer(Renderer);
		if (Window)
			SDL_DestroyWindow(Window);
	}

	SDL_Quit();
	return 0;
}