#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()
{
	m_window = nullptr;
	m_screen_width = 1280;
	m_screen_hight = 720;
	m_game_state = GameState::PLAY;
	xpos = -10, ypos = 50, zpos = 50;
	hrot = 0, vrot = -45;
}

void MainGame::Run()
{
	Init();
	GameLoop();
}

void MainGame::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Heightmap Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_width, m_screen_hight, SDL_WINDOW_OPENGL);
	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	GLenum error = glewInit();

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);

	SDL_GL_SetSwapInterval(1);
	SDL_SetWindowFullscreen(m_window, GL_FALSE);

	heightmap.Load("HeightMap/terrain3.png", 100, 100, 5, "Texture/grass.jpg");

}

void MainGame::GameLoop()
{
	while (m_game_state != GameState::EXIT)
	{
		ProcessInput();
		DrawGame();
	}
}

void MainGame::ProcessInput()
{
	while (SDL_PollEvent(&evnt))
	{
		if (evnt.type == SDL_QUIT)
		{
			m_game_state = GameState::EXIT;
		}
		ProcessKeyPress();
	}
}

float MainGame::ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

void MainGame::DrawGame()
{
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	float verticalAngle = ToRad(vrot);
	float horizontalAngle = ToRad(hrot);

	float dx = cos(verticalAngle) * cos(horizontalAngle);
	float dy = cos(verticalAngle) * sin(horizontalAngle);
	float dz = sin(verticalAngle);

	float cx = xpos + dx, cy = ypos + dy, cz = zpos + dz;
	gluLookAt(xpos, ypos, zpos, cx, cy, cz, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 500.0f);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	heightmap.DrawHeightMap();
	glPopMatrix();

	SDL_GL_SwapWindow(m_window);
}

void MainGame::ProcessKeyPress()
{
	if (evnt.type == SDL_KEYDOWN)
	{
		if (m_game_state == GameState::PLAY)
		{
			switch (evnt.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_game_state = GameState::EXIT;
				break;
			}
		}
	}
}

