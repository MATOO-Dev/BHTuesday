#pragma once

#include <SDL.h>

const static int windowWidth = 600;
const static int windowHeight = 1000;
const static int scrollSpeed = 50;

static SDL_Color white = { 255, 255, 255 };
static SDL_Color black = { 0, 0, 0 };
static SDL_Color yellow = { 255, 255, 0 };
static SDL_Color magenta = { 255, 0, 255 };
static SDL_Color aqua = { 0, 255, 255 };

enum class EControlStyle	//defines whether the player is controlled using keyboard controls or the mouse
{
	Keyboard,
	Mouse
};

enum class EGameState		//defines what state the game is in
{
	MainMenu,
	LevelSelectMenu,
	PauseMenu,
	DeathMenu,
	VictoryMenu,
	SettingsMenu,
	EditorMenu,
	UpgradesMenu,
	Active
};

enum class ETheme		//defines the current theme
{
	Light,
	Dark
};

enum class EEnemyType		//defines an enemys type
{
	Null,
	Pellets,
	Beam,
	Kamikaze
};

enum class EEnemyState		//defines the current state of an enemy
{
	Intro,
	Idle,
	Shoot,
	Outro
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
	StartGame,
	QuitGame
};