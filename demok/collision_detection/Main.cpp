#include "Calcs3D.h"
#include <iostream>
#include <GLUT.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

Vec3 position;
Vec3 pose;
Vec3 direction;

//Változók az állapotok kezeléséhez, mivel nincs sok így nincs külön osztályban, de úgy célszerûbb
bool go_forward = false, go_backward = false;
bool look_up = false, look_down = false;
bool turn_left = false, turn_right = false;
bool go_left = false, go_right = false;

Vec3 Triangle[3];
Vec3 Triangle2[3];
Vec3 Line[2];

bool bCollided = false, bCollided2 = false;
Calcs3D Math;

/**
		*Értékek beállítása
*/
void Init()
{
	position.SetValues(0, 0.5, -2);
	pose.SetValues(0, 0, 0);

	Triangle[0].SetValues(-5.0f, 6.0f, -5.0f);
	Triangle[1].SetValues(5.0f, 6.0f, -5.0f);
	Triangle[2].SetValues(0.0f, 6.0f, 10.0f);

	Triangle2[0].SetValues(-5.0f, 0.0f, 10.0f);
	Triangle2[1].SetValues(5.0f, 0.0f, 12.0f);
	Triangle2[2].SetValues(0.0f, 5.0f, 10.0f);

	Line[0].SetValues(position.x, 0.3f, position.z);
	Line[1].SetValues(0.0f, 0.5f, 0.0f);
}

/**
		*Ablak méretezése
*/
static void Resize(int width, int height)    
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

/**
		*Ablak frissítése másodpercenként 60x
*/
void Timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, Timer, 0);
	if (go_forward == true) {
		position.x += (float)sin(pose.y*3.14f / 180.0f) * 0.2f;
		position.z += (float)cos(pose.y*3.14f / 180.0f) * 0.2f;
	}
	if (go_backward == true) {
		position.x -= (float)sin(pose.y*3.14f / 180.0f) * 0.2f;
		position.z -= (float)cos(pose.y*3.14f / 180.0f) * 0.2f;
	}
	if (go_left == true) {
		position.x += (float)cos(pose.y*3.14f / 180.0f) * 0.15f;
		position.z += (float)sin(pose.y*3.14f / 180.0f) * -0.15f;
	}
	if (go_right == true) {
		position.x -= (float)cos(pose.y*3.14f / 180.0f) * 0.15f;
		position.z -= (float)sin(pose.y*3.14f / 180.0f) * -0.15f;
	}

	Line[0].x = position.x;
	Line[0].y = position.y - 0.01f;
	Line[0].z = position.z;

	Line[1].x = position.x + (direction.x * 100);
	Line[1].y = position.y + (direction.y * 100);
	Line[1].z = position.z + (direction.z * 100);

	if (look_up == true) {
		if (pose.x >= 87.0f) {
			pose.x = 87.0f;
		}
		else {
			pose.x += 1.0f;
		}
	}

	if (look_down == true) {
		if (pose.x <= -87.0f) {
			pose.x = -87.0f;
		}
		else {
			pose.x -= 1.0f;
		}
	}
	if (turn_left == true) {
		pose.y += 1.0f;
	}
	if (turn_right == true) {
		pose.y -= 1.0f;
	}
}

/**
		*Elemek kirajzolása
*/
static void Display(void)                
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	/*mozgás, forgás*/glMatrixMode(GL_MODELVIEW);
	float verticalAngle = ToRad(pose.x);
	float horizontalAngle = ToRad(pose.y);

	direction.x = cos(verticalAngle) * sin(horizontalAngle);
	direction.y = sin(verticalAngle);
	direction.z = cos(verticalAngle) * cos(horizontalAngle);

	float a = 0, b = 1, c = 0;

	float cx = position.x + direction.x, cy = position.y + direction.y, cz = position.z + direction.z;

	gluLookAt(position.x, position.y, position.z, cx, cy, cz, a, b, c);/*mozgás, forgás vége*/

	bCollided = Math.IntersectedTriangle(Triangle, Line, 3);
	bCollided2 = Math.IntersectedTriangle(Triangle2, Line, 3);

	glBegin(GL_TRIANGLES);
	if (bCollided)
		glColor3ub(0, 255, 0);
	else
		glColor3ub(255, 0, 0);
	glVertex3f(Triangle[0].x, Triangle[0].y, Triangle[0].z);					
	glVertex3f(Triangle[1].x, Triangle[1].y, Triangle[1].z);				
	glVertex3f(Triangle[2].x, Triangle[2].y, Triangle[2].z);
	glEnd();

	glBegin(GL_TRIANGLES);
	if (bCollided2)
		glColor3ub(0, 255, 0);
	else
		glColor3ub(255, 0, 0);
	glVertex3f(Triangle2[0].x, Triangle2[0].y, Triangle2[0].z);
	glVertex3f(Triangle2[1].x, Triangle2[1].y, Triangle2[1].z);
	glVertex3f(Triangle2[2].x, Triangle2[2].y, Triangle2[2].z);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);	
	glColor3ub(255, 255, 255);
	glVertex3f(Line[0].x, Line[0].y, Line[0].z);
	glVertex3f(Line[1].x, Line[1].y, Line[1].z);
	glEnd();

	glutSwapBuffers();                
}

/**
		*Billentyû lenyomásának figyelése
*/
static void ProcessKeyPress(unsigned char key, int x, int y)
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
	case '4':                                        
		turn_left = true;
		break;
	case '6':                                        
		turn_right = true;
		break;
	case '8':
		look_up = true;
		break;
	case '5':
		look_down = true;
		break;
	}          
}

/**
		*Billentyû felengedésének figyelése
*/
static void ProcessKeyRelease(unsigned char key, int x, int y)
{
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
	case '4':
		turn_left = false;
		break;
	case '6':
		turn_right = false;
		break;
	case '8':
		look_up = false;
		break;
	case '5':
		look_down = false;
		break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);                 
	glutInitWindowPosition(0, 0);              
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("Bullet demo");         
								
	Init();

	glutReshapeFunc(Resize);
	glutDisplayFunc(Display);
	glutKeyboardFunc(ProcessKeyPress);
	glutKeyboardUpFunc(ProcessKeyRelease);
	glutTimerFunc(0, Timer, 0);
         
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();

	return 0;
}