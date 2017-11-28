#pragma once
#include "VboDrawer.h"
#include <SDL2/SDL.h>
#include <glew.h>
#include <glut.h>
#include <SOIL.h>

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();

	/**
			*Futtatás
	*/
	void Run();

private:
	/**
			*Elemek inicializálása
	*/
	void Init();


	void GameLoop();

	/**
			*Bevitel figyelése
	*/
	void ProcessInput();

	/**
			*Elemek kirajzolása
	*/
	void DrawGame();

	/**
			*A billentyûk lenyomásának figyelése
	*/
	void ProcessKeyPress();

	/**
			*Szög radiánba váltása
	*/
	float ToRad(float angle_degrees);

	VboDrawer raptor;

	SDL_Window *m_window;
	SDL_Cursor* cursor;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;
	float xpos, ypos, zpos;
	float hrot, vrot;
	float raptor_rotation;
};

