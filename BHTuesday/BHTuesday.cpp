// BHTuesday.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "CPlayer.h"
#include "CEnemy.h"
#include "CProjectile.h"
#include "Defines.h"
#include "CGameManager.h"

#define TICK_INTERVAL 16


int main(int argc, char* argv[])
{
	bool running = false;

	CGameManager GameManager(running);


	if (GameManager.InitializeSDL())
		running = true;

	if (running)
		GameManager.InitializeGameState(EGameState::MainMenu);


	//game loop
	while (running)
	{
		int before = SDL_GetTicks();
		SDL_Event event;

		GameManager.Update((float)TICK_INTERVAL / 1000.f);

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
				switch (event.type)
				{
				case (SDL_MOUSEMOTION):
					//used for potential hovering over buttons
					break;
				case(SDL_MOUSEBUTTONDOWN):
					GameManager.UpdateButtons(event.button);
					break;
				case(SDL_QUIT):
					running = false;
					break;
				default:
					break;
				}
			}
		}
	}

	GameManager.ExitGame();
	return 0;
}