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
			*Futtat�s
	*/
	void Run();

private:
	/**
			*Elemek inicializ�l�sa
	*/
	void Init();


	void GameLoop();

	/**
			*Bevitel figyel�se
	*/
	void ProcessInput();

	/**
			*Elemek kirajzol�sa
	*/
	void DrawGame();

	/**
			*A billenty�k lenyom�s�nak figyel�se
	*/
	void ProcessKeyPress();

	/**
			*Sz�g radi�nba v�lt�sa
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

