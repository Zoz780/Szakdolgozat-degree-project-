#pragma once
#include "VboDrawer.h"
#include "Character.h"
#include "Action.h"
#include <SDL2/SDL.h>
#include <glew.h>
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
	double CalcElapsedTime();
	void ProcessKeyPress();
	void ProcessKeyRelease();
	void CameraMovementHandler(double elapsed_time);
	float ToRad(float angle_degrees);

	VboDrawer floor;
	Character robot;
	Action action;

	SDL_Window *m_window;
	SDL_Cursor* cursor;
	SDL_Event evnt;
	GameState m_game_state;
	int m_screen_width;
	int m_screen_hight;
	float xpos, ypos, zpos;
	float hrot, vrot;
	double m_time;
};

