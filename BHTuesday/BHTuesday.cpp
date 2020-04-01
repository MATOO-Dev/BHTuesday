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
	//initialize variables
	static EGameState activeGameState = EGameState::MainMenu;
	/*
	std::vector<CProjectile> EnemyBullets;
	std::vector<CProjectile> PlayerBullets;
	std::vector<CEnemy> Enemys;
	static CPlayer* myPlayer = new CPlayer(CVector2(300, 875), PlayerBullets);
	*/
	TTF_Init();
	CGameManager GameManager;

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_Window* Window = NULL;
		SDL_Renderer* Renderer = NULL;

		//create a window using sdl
		if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &Window, &Renderer) == 0)
		{
			SDL_bool completed = SDL_FALSE;
			if (GameManager.InitializeSDL(Renderer) == false)
			{
			}

			//game loop
			while (!completed)
			{
				int before = SDL_GetTicks();
				SDL_Event event;
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(Renderer);
				SDL_SetRenderDrawColor(Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

				//manages current Game State
				switch (activeGameState)
				{
				case(EGameState::MainMenu):
					GameManager.RenderAll();
					break;
				case(EGameState::Active):
					//GameManager.UpdateAll();
					//GameManager.RenderAll();
					/*
					myPlayer->Update((float)TICK_INTERVAL / 1000.f, myControlStyle);
					myPlayer->Render(*Renderer);
					for (int i = 0; i < Enemys.size(); i++)
					{
						Enemys[i].Update((float)TICK_INTERVAL / 1000.f);
						Enemys[i].Render(*Renderer);
					}
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
					break;
				case(EGameState::PauseMenu):
					//GameManager.RenderAll();

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
	TTF_Quit();
	return 0;
}