#include "PathFinder.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

float *x, *y;
Vec2 multiplier;
float dynamic_width, dynamic_height;
Vec2 finish_point;

PathFinder pathfinder;

/**
		*�rt�kek felsk�l�z�sa az adott ablak felbont�s�hoz
*/
void CalcLimits(int width, int height)
{
	multiplier.x = (width / pathfinder.GetGridSize()) * 0.98; //Szorozva 0.98-al, hogy ne pont az ablak sz�l�re essen a rajz v�ge
	multiplier.y = (height / pathfinder.GetGridSize()) * 0.98; //Szorozva 0.98-al, hogy ne pont az ablak sz�l�re essen a rajz v�ge
}

/**
		*Ablak m�retez�se
*/
static void Resize(int width, int height)    
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	dynamic_width = width;
	dynamic_height = height;
	CalcLimits(width, height); //�tm�retez�s eset�n a felsk�l�z�s �jrasz�mol�sa
}

/**
		*F�ggv�ny rajzol�sa OpenGL-el
*/
static void Display(void)                
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f); //Alap sz�n k�k
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	
	pathfinder.Draw(multiplier.x, multiplier.y); //�tvonal kirajzol� f�ggv�ny h�v�sa

	glutSwapBuffers();                
}

/**
		*Billenty�k lenyom�s�nak figyel�se
*/
static void ProcessKeyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (finish_point.y > 0)
		{
			finish_point.y -= 1;
			pathfinder.Search(finish_point.x, finish_point.y);
		}
		break;
	case 's':
		if (finish_point.y < pathfinder.GetGridSize() - 1)
		{
			finish_point.y += 1;
			pathfinder.Search(finish_point.x, finish_point.y);
		}
		break;
	case 'a':
		if (finish_point.x > 0)
		{
			finish_point.x -= 1;
			pathfinder.Search(finish_point.x, finish_point.y);
		}
		break;
	case 'd':
		if (finish_point.x < pathfinder.GetGridSize() - 1)
		{
			finish_point.x += 1;
			pathfinder.Search(finish_point.x, finish_point.y);
		}
		break;
	}
}

/**
		*F�ggv�ny az ablakfriss�t�shez
*/
void Timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, Timer, 0);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);              
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("A-star Demo");       
	
	finish_point.x = (pathfinder.GetGridSize() / 2) + 2;
	finish_point.y = (pathfinder.GetGridSize() / 2) + 2;
	pathfinder.Search(finish_point.x, finish_point.y);

	glutReshapeFunc(Resize);
	glutKeyboardFunc(ProcessKeyPress);
	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);
	glutMainLoop();
	return 0;
}