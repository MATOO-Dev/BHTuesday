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
	CGameManager GameManager;

	SDL_bool running = SDL_FALSE;

	if (GameManager.InitializeSDL())
		running = SDL_TRUE;

	if (running)
		GameManager.InitializeMenu(EGameState::MainMenu);


	//game loop
	while (running)
	{
		int before = SDL_GetTicks();
		SDL_Event event;

		GameManager.Update();

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
					running = SDL_FALSE;
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

/*
for (int i = 0; i < EnemyBullets.size(); i++)
{
	EnemyBullets[i].Update((float)TICK_INTERVAL / 1000.f);
	EnemyBullets[i].Collision(*myPlayer);
	if (EnemyBullets[i].inBounds() == false)
	{
		EnemyBullets.erase(EnemyBullets.begin() + i);
	}
	EnemyBullets[i].Render(Renderer);
}
for (int i = 0; i < PlayerBullets.size(); i++)
{
	PlayerBullets[i].Update((float)TICK_INTERVAL / 1000.f);
	if (PlayerBullets[i].inBounds() == false)
	{
		std::cout << "bullet" << i << "is out of bounds" << std::endl;
		//PlayerBullets.erase(EnemyBullets.begin() + i);
		//PlayerBullets.erase(EnemyBullets.begin() + 0);
	}
	PlayerBullets[i].Render(Renderer);
}
*/