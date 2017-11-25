#include "MainGame.h"
#include <iostream>

using namespace std;

MainGame::MainGame()
{
	m_window = nullptr;
	m_screen_width = 1280;
	m_screen_hight = 720;
	m_game_state = GameState::PLAY;
	xpos = 0, ypos = 0, zpos = 20;
	hrot = 0, vrot = -18;
}

void MainGame::Run()
{
	Init();
	GameLoop();
}

void MainGame::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Animation Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_width, m_screen_hight, SDL_WINDOW_OPENGL);
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

	robot.Load();

	floor.Load("Models/floor.obj", 26.15f, 0.25f, 26.15f, "Textures/floor.jpg");
}

double MainGame::CalcElapsedTime()
{
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - m_time);
	double elapsed_time_in_secs = elapsed_time / 1000.0;
	m_time = current_time;

	if (elapsed_time_in_secs < 0.0 || elapsed_time_in_secs > 1.0) {
		elapsed_time_in_secs = 0.0;
	}
	return elapsed_time_in_secs;
}

void MainGame::GameLoop()
{
	double elapsed_time;
	while (m_game_state != GameState::EXIT)
	{
		elapsed_time = CalcElapsedTime();
		ProcessInput();
		CameraMovementHandler(elapsed_time);
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
		ProcessKeyRelease();
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

	float x_cam = xpos - (dx * 35);
	float y_cam = ypos - (dy * 35);
	float z_cam = zpos - (dz * 35);

	float cx = xpos + dx, cy = ypos + dy, cz = zpos + dz;

	if (!action.getCameraView())
	{
		robot.SetXpos(xpos);
		robot.SetYpos(ypos);
		gluLookAt(x_cam, y_cam, z_cam, cx, cy, cz, 0, 0, 1);
	}
	else
	{
		gluLookAt(xpos, ypos, zpos, cx, cy, cz, 0, 0, 1);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, (GLfloat)m_screen_width / (GLfloat)m_screen_hight, 0.01f, 1000.0f);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glRotatef(90.0f, 1, 0, 0);
	floor.DrawModel(-100, 0.1, -100);
	floor.DrawModel(-100, 0.1, 100);
	floor.DrawModel(100, 0.1, 100);
	floor.DrawModel(100, 0.1, -100);
	glPopMatrix();

	robot.Draw();

	SDL_GL_SwapWindow(m_window);
}

void MainGame::CameraMovementHandler(double elapsed_time)
{
	if (action.getCameraView())
	{
		if (action.needGoForward()) {
			double angle = hrot * M_PI / 180.0f;
			xpos += cos(angle) * 40.0f * elapsed_time;
			ypos += sin(angle) * 40.0f * elapsed_time;
		}

		if (action.needGoBackward()) {
			double angle = hrot * M_PI / 180.0f;
			xpos -= cos(angle) * 40.0f * elapsed_time;
			ypos -= sin(angle) * 40.0f * elapsed_time;
		}

		if (action.needTurnLeft()) {
			hrot += 100.0f * elapsed_time;
		}

		if (action.needTurnRight()) {
			hrot -= 100.0f * elapsed_time;
		}
		if (action.needGoUp())
		{
			zpos += 40.0f * elapsed_time;
		}
		if (action.needGoDown())
		{
			if (zpos > 10.0f)
			{
				zpos -= 40.0f * elapsed_time;
			}
			else zpos = 10.0f;
		}
	}
	else
	{
		if (action.needGoForward()) {
			double angle = hrot * M_PI / 180.0f;
			xpos += cos(angle) * 25.0f * elapsed_time;
			ypos += sin(angle) * 25.0f * elapsed_time;
			robot.Animate(elapsed_time);
			action.stopBackward();
		}

		if (action.needGoBackward()) {
			double angle = hrot * M_PI / 180.0f;
			xpos -= cos(angle) * 25.0f * elapsed_time;
			ypos -= sin(angle) * 25.0f * elapsed_time;
			robot.Animate(elapsed_time);
			action.stopForward();
		}

		if (action.needTurnLeft()) {
			hrot += 60.0f * elapsed_time;
			robot.Turn(hrot);
		}

		if (action.needTurnRight()) {
			hrot -= 60.0f * elapsed_time;
			robot.Turn(hrot);
		}
	}
}

void MainGame::ProcessKeyPress()
{
	if (evnt.type == SDL_KEYDOWN)
	{
		if (m_game_state == GameState::PLAY)
		{
			switch (evnt.key.keysym.sym)
			{
			case 'w':
				action.startGoForward();
				break;
			case 's':
				action.startGoBackward();
				break;
			case 'a':
				action.startTurnLeft();
				break;
			case 'd':
				action.startTurnRight();
				break;
			case SDLK_ESCAPE:
				m_game_state = GameState::EXIT;
				break;
			}
			if (action.getCameraView())
			{
				switch (evnt.key.keysym.sym)
				{
				case 'c':
					action.changeCameraView();		
					xpos = robot.GetXpos();
					ypos = robot.GetYpos();
					zpos = 20;
					hrot = robot.GetTurn();
					break;
				case 'x':
					action.startGoDown();
					break;
				case SDLK_SPACE:
					action.startGoUp();
					break;
				}
			}
			else
			{
				switch (evnt.key.keysym.sym)
				{
				case 'c':
					action.changeCameraView();
					zpos = 30;
					break;
				}
			}
		}
	}
}

void MainGame::ProcessKeyRelease()
{
	if (evnt.type == SDL_KEYUP)
	{
		switch (evnt.key.keysym.sym)
		{
		case 'w':
			action.stopForward();
			break;
		case 's':
			action.stopBackward();
			break;
		case 'a':
			action.stopTurnLeft();
			break;
		case 'd':
			action.stopTurnRight();
			break;
		case 'x':
			action.stopGoDown();
			break;
		case SDLK_SPACE:
			action.stopGoUp();
			break;
		}
	}
}

