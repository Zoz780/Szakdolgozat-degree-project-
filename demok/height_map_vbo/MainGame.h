#pragma once
#include "DrawHeightMapVBO.h"
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
	void Run();

private:
	void Init();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
	void ProcessKeyPress();
	float ToRad(float angle_degrees);

	DrawHeightMapVBO heightmap;

	SDL_Window *m_window;
	SDL_Cursor* cursor;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;
	float xpos, ypos, zpos;
	float hrot, vrot;
};

