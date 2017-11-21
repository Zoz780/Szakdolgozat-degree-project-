#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include <stdlib.h>
#include <time.h> 
#include <GLUT.h>
using namespace std;

#define NUM_OF_ENEMIES 5

const int m_screen_width = 1280;
const int m_screen_hight = 720;
bool go_forward = false;
bool go_backward = false;
bool go_right = false;
bool go_left = false;
bool is_moving = false;
double m_time = 0.0;
bool is_alive_array[NUM_OF_ENEMIES];
bool is_alive = true;
double elapsed_time;

Player player;
Enemy enemy[NUM_OF_ENEMIES];

void Init()
{
	srand(time(NULL));
	float posx, posy, speed, fear;
	printf("NEW ROUND!\n");
	for (int i = 0; i < NUM_OF_ENEMIES; i++)
	{
		is_alive_array[i] = true;
		posx = rand() % 1270 + 5;
		posy = rand() % 710 + 5;
		speed = rand() % (8 + 1 - 2) + 2;

		if (speed > 5.0f)
		{
			fear = rand() % (50 + 1 - 25) + 25;
		}
		else if ((speed > 3.0f) && (speed <= 5.0f))
		{
			fear = rand() % (110 + 1 - 50) + 50;
		}
		else if (speed <= 3.0f)
		{
			fear = rand() % (180 + 1 - 110) + 110;
		}
		enemy[i].SetPosX(posx);
		enemy[i].SetPosY(posy);
		enemy[i].SetCharacteristics(fear, speed);
		printf("\tNew Enemy (number %d):\n\t\tFear: %f, speed: %f\n", i+1, fear, speed);
	}
}

double CalcElapsedTime()
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

static void resize(int width, int height)    
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 120, timer, 0);
	elapsed_time = CalcElapsedTime();
	float posx, posy;

	for (int i = 0; i < NUM_OF_ENEMIES; i++)
	{
		enemy[i].MoveToDestination(elapsed_time);
	}

	if (go_forward)
	{
		posy = player.GetPosY();
		posy -= (5.0f * elapsed_time) * 25;
		player.SetPosY(posy);
	}
	if (go_backward)
	{
		posy = player.GetPosY();
		posy += (5.0f * elapsed_time) * 25;
		player.SetPosY(posy);
	}
	if (go_left)
	{
		posx = player.GetPosX();
		posx -= (5.0f * elapsed_time) * 25;
		player.SetPosX(posx);
	}
	if (go_right)
	{
		posx = player.GetPosX();
		posx += (5.0f * elapsed_time) * 25;
		player.SetPosX(posx);
	}

}

static void display(void)              
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	if ((go_forward) || (go_backward) || (go_left) || (go_right))
	{
		is_moving = true;
	}
	else
		is_moving = false;

	for (int i = 0; i < NUM_OF_ENEMIES; i++)
	{
		enemy[i].Draw();
		enemy[i].SetDestinaiton(player.GetPosX(), player.GetPosY(), is_moving);
		is_alive_array[i] = enemy[i].SetRoundEnd(player.GetPosX(), player.GetPosY());
	}
	if ((!is_alive_array[0]) || (!is_alive_array[1]) || (!is_alive_array[2]) || (!is_alive_array[3]) || (!is_alive_array[4]))
	{
		is_alive = false;
	}
	else
	{
		is_alive = true;
	}
	player.Draw();

	glPopMatrix();
	glutSwapBuffers();                

}

static void key(unsigned char key, int x, int y)
{
	if (is_alive)
	{
		switch (key)
		{
		case 'w':
			go_forward = true;
			break;
		case 's':
			go_backward = true;
			break;
		case 'a':
			go_left = true;
			break;
		case 'd':
			go_right = true;
			break;
		}
	}
	else
	{
		go_forward = false;
		go_backward = false;
		go_left = false;
		go_right = false;
	}
	switch (key)
	{
	case 'r':
		Init();
		break;
	}

	glutPostRedisplay();          
}

static void keyup(unsigned char key, int x, int y)
{
	float posx, posy;
	switch (key)
	{
	case 'w':
		go_forward = false;
		break;
	case 's':
		go_backward = false;
		break;
	case 'a':
		go_left = false;
		break;
	case 'd':
		go_right = false;
		break;
	}

	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(m_screen_width, m_screen_hight);                
	glutInitWindowPosition(100, 100);             
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("Behavior Demo");
	Init();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyup);
	glutTimerFunc(0, timer, 0);

	glClearColor(0.0, 0.0, 0.0, 1);                 

	glutMainLoop();

	return 0;
}