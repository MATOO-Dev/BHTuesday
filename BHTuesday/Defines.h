#pragma once

const static int windowWidth = 600;
const static int windowHeight = 1000;
/*
static SDL_Color white = { 255, 255, 255 };
static SDL_Color black = { 0, 0, 0 };
static SDL_Color yellow = { 255, 255, 0 };
static SDL_Color magenta = { 255, 0, 255 };
static SDL_Color aqua = { 0, 255, 255 };
*/

enum class EControlStyle	//defines whether the player is controlled using keyboard controls or the mouse
{
	Keyboard,
	Mouse
};

enum class EGameState		//defines what state the game is in
{
	MainMenu,
	LevelSelectMenu,
	Active,
	PauseMenu,
	SettingsMenu,
	EditorMenu,
	UpgradesMenu
};

enum class ETheme		//defines the current theme
{
	Light,
	Dark
};

enum class EEnemyType		//defines the current theme
{
	Sphere,
	Dark
};

enum class EButtonAction		//defines the more explicit action of the current button
{
	None,
	OpenMainMenu,
	OpenLevelSelectMenu,
	OpenPauseMenu,
	OpenSettingsMenu,
	OpenEditorMenu,
	OpenUpgradesMenu,
	StartGame
};

/*
// Asteroids.cpp : Defines the entry point for the console application.
#define TICK_INTERVAL 16

int main(int argc, char* argv[])
{
	CPlayer* MyPlayer = new CPlayer();
	CPlayerControl MyPlayerControl = CPlayerControl(*MyPlayer);

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {

				int before = SDL_GetTicks();
				SDL_Event event;

				{
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				}

				MyPlayer->Render(*renderer);
				//MyPlayer->Update((float)TICK_INTERVAL / 1000.f);
				MyPlayerControl.Update((float)TICK_INTERVAL / 1000.f);

				SDL_RenderPresent(renderer);

				int after = SDL_GetTicks();
				int ticks = after - before;

				if (ticks < 16)
				{
					SDL_Delay(16 - ticks);
				}
				ticks = SDL_GetTicks() - before;
				std::cout << ticks << "\n";

				while (SDL_PollEvent(&event)) {
					if (event.ty e == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
}

////////////////////////////////////////////////////
CPlayer
//////////////////////////////////////////////
#include "CPlayer.h"

CPlayer::CPlayer() :
	m_Offsets(),
	m_Position(CVector2(320, 220)),
	m_Heading(0),
	m_Velocity(CVector2(m_Heading) * 100.0f)
{}

void CPlayer::Update(float timer)
{
	m_Position = m_Position + (m_Velocity * timer);
	m_Velocity = m_Velocity * 0.98f;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		m_Velocity = m_Velocity + CVector2(m_Heading) * (350 * timer);
	}
	if (state[SDL_SCANCODE_A]) {
		m_Heading -= (180 * timer);
	}
	if (state[SDL_SCANCODE_D]) {
		m_Heading += (180 * timer);
	}
	if (state[SDL_SCANCODE_SPACE]) {
	}

}

void CPlayer::Render(SDL_Renderer& renderer) const
{
	std::vector<CVector2> rotatedOffsets;
	for (int i = 0; i < m_Offsets.size(); i++) {
		rotatedOffsets.push_back(m_Offsets[i]);
		rotatedOffsets[i].rotate(m_Heading);
	}
	for (int i = 0; i < rotatedOffsets.size(); i++)
	{
		CVector2 From = m_Position + rotatedOffsets[i];
		CVector2 To;

		if (i < rotatedOffsets.size() - 1)
			To = m_Position + rotatedOffsets[i + 1];

		else
			To = m_Position + rotatedOffsets[0];

		SDL_RenderDrawLine(&renderer, (int)From.x, (int)From.y, (int)To.x, (int)To.y);
	}
}

////////////////////////////////////////////
CPlayerControl
/////////////////////////////////////////

#include "CPlayerControl.h"

CPlayerControl::CPlayerControl(CPlayer& controlledPlayer) :
	m_ControlledObject(controlledPlayer)
{}

void CPlayerControl::Update(float timer)
{
	m_ControlledObject.SetPosition(m_ControlledObject.GetPosition() + (m_ControlledObject.GetVelocity() * timer));
	m_ControlledObject.SetVelocity(m_ControlledObject.GetVelocity() * 0.98f);
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W]) {
		m_ControlledObject.SetVelocity(m_ControlledObject.GetVelocity() + CVector2(m_ControlledObject.GetHeading()) * (350 * timer));
	}
	if (state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_LSHIFT]) {
		m_ControlledObject.SetHeading(-180 * timer);
	}
	if (state[SDL_SCANCODE_D] && !state[SDL_SCANCODE_LSHIFT]) {
		m_ControlledObject.SetHeading(180 * timer);
	}
	if (state[SDL_SCANCODE_SPACE]) {
	}
	int strafeSpeed = 200;
	if (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_LSHIFT])
	{
		CVector2 strafeVector = m_ControlledObject.GetHeading();
		strafeVector.rotate(-90);
		m_ControlledObject.SetVelocity(m_ControlledObject.GetVelocity() + (strafeVector * (strafeSpeed * timer)));
	}
	if (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_LSHIFT])
	{
		CVector2 strafeVector = m_ControlledObject.GetHeading();
		strafeVector.rotate(90);
		m_ControlledObject.SetVelocity(m_ControlledObject.GetVelocity() + (strafeVector * (strafeSpeed * timer)));
	}
}
*/