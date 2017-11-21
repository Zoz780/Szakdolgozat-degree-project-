#include "Vec3.h"
#include <iostream>
#include <GLUT.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * 3.14 / 180.0f;
}

Vec3 position;
Vec3 rotation;
bool go_forward = false, go_backward = false;
bool look_up = false, look_down = false;
bool turn_left = false, turn_right = false;
bool go_left = false, go_right = false;
int control_flag = 0;

Vec3 upper_rotation;
Vec3 lower_rotation;
bool change_fw = false, change_bw = false, change_l = false, change_r = false;

GLfloat light_ambient[] = { 0.8f,0.8f,0.8f,1.0f };

Vec3 Plane[4];
Vec3 Upper[2];
Vec3 Lower[2];

void init()
{
	position.InitValues(0, 0.5, -2);
	rotation.InitValues(0, 0, 0);
	lower_rotation.InitValues(0, 0, 0);
	upper_rotation.InitValues(0, 0, 0);
	Plane[0].InitValues(-10, -1, -10);
	Plane[1].InitValues(10, -1, -10);
	Plane[2].InitValues(10, -1, 10);
	Plane[3].InitValues(-10, -1, 10);
	Upper[0].InitValues(1, 1, 1);
}

static void resize(int width, int height)    
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	if (go_forward == true) {
		position.x += (float)sin(rotation.y*3.14f / 180.0f) * 0.2f;
		position.z += (float)cos(rotation.y*3.14f / 180.0f) * 0.2f;
	}
	if (go_backward == true) {
		position.x -= (float)sin(rotation.y*3.14f / 180.0f) * 0.2f;
		position.z -= (float)cos(rotation.y*3.14f / 180.0f) * 0.2f;
	}
	if (go_left == true) {
		position.x += (float)cos(rotation.y*3.14f / 180.0f) * 0.15f;
		position.z += (float)sin(rotation.y*3.14f / 180.0f) * -0.15f;
	}
	if (go_right == true) {
		position.x -= (float)cos(rotation.y*3.14f / 180.0f) * 0.15f;
		position.z -= (float)sin(rotation.y*3.14f / 180.0f) * -0.15f;
	}

	if (look_up == true) {
		if (rotation.x >= 87.0f) {
			rotation.x = 87.0f;
		}
		else {
			rotation.x += 1.0f;
		}
	}

	if (look_down == true) {
		if (rotation.x <= -87.0f) {
			rotation.x = -87.0f;
		}
		else {
			rotation.x -= 1.0f;
		}
	}
	if (turn_left == true) {
		rotation.y += 1.0f;
	}
	if (turn_right == true) {
		rotation.y -= 1.0f;
	}

	if (change_fw == true)
	{
		switch (control_flag)
		{
		case 0:
			if (Upper[0].z < 4.0f)
			{
				Upper[0].z += 0.2f;
			}
			else
				Upper[0].z == 4.0f;
			break;
		case 1:
			upper_rotation.y -= 2.0f;
			break;
		case 2:
			lower_rotation.y -= 2.0f;
			break;
		}
	}

	if (change_bw == true)
	{
		switch (control_flag)
		{
		case 0:
			if (Upper[0].z > -4.0f)
			{
				Upper[0].z -= 0.2f;
			}
			else
				Upper[0].z == -4.0f;
			break;
		case 1:
			upper_rotation.y += 2.0f;
			break;
		case 2:
			lower_rotation.y += 2.0f;
			break;
		}
	}

	if (change_l == true)
	{
		switch (control_flag)
		{
		case 0:
			if (Upper[0].x < 4.0f)
			{
				Upper[0].x += 0.2f;
			}
			else
				Upper[0].x = 4.0f;
			break;
		case 1:
			upper_rotation.x -= 2.0f;
			break;
		case 2:
			lower_rotation.x -= 2.0f;
			break;
		}
	}

	if (change_r == true)
	{
		switch (control_flag)
		{
		case 0:
			if (Upper[0].x > -4.0f)
			{
				Upper[0].x -= 0.2f;
			}
			else 
				Upper[0].x = -4.0f;
			break;
		case 1:
			upper_rotation.x += 2.0f;
			break;
		case 2:
			lower_rotation.x += 2.0f;
			break;
		}
	}
}

void set_far_point(float h_rot, float v_rot, Vec3 pos, float *far_x, float *far_y, float *far_z)
{
	float verticalAngle = ToRad(h_rot);
	float horizontalAngle = ToRad(v_rot);

	float dx = cos(verticalAngle) * sin(horizontalAngle);
	float dy = sin(verticalAngle);
	float dz = cos(verticalAngle) * cos(horizontalAngle);

	*far_x = pos.x + dx, *far_y = pos.y + dy, *far_z = pos.z + dz;
}

void draw_joint(float x, float y, float z)
{
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	GLUquadric* joint = gluNewQuadric();
	gluQuadricDrawStyle(joint, GLU_FILL);
	gluQuadricOrientation(joint, GLU_OUTSIDE);
	gluQuadricNormals(joint, GLU_SMOOTH);
	glTranslatef(x, y, z);
	gluSphere(joint, 0.05, 25, 25);
	gluDeleteQuadric(joint);
	glEnd();
	glPopMatrix();
}


static void display(void)                
{

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	/*mozgás, forgás*/glMatrixMode(GL_MODELVIEW);

	Vec3 far_point;
	set_far_point(rotation.x, rotation.y, position, &far_point.x, &far_point.y, &far_point.z);
	gluLookAt(position.x, position.y, position.z, far_point.x, far_point.y, far_point.z, 0, 1, 0);
	/*mozgás, forgás vége*/
	
	switch (control_flag)
	{
	case 0:

	case 1:
		set_far_point(upper_rotation.y, upper_rotation.x, Upper[0], &Upper[1].x, &Upper[1].y, &Upper[1].z);
		Lower[0].x = Upper[1].x;
		Lower[0].y = Upper[1].y;
		Lower[0].z = Upper[1].z;
	case 2:
		Lower[0].x = Upper[1].x;
		Lower[0].y = Upper[1].y;
		Lower[0].z = Upper[1].z;
		set_far_point(lower_rotation.y, lower_rotation.x, Lower[0], &Lower[1].x, &Lower[1].y, &Lower[1].z);
	}

	draw_joint(Upper[0].x, Upper[0].y, Upper[0].z);
	draw_joint(Lower[0].x, Lower[0].y, Lower[0].z);
	draw_joint(Lower[1].x, Lower[1].y, Lower[1].z);

	glBegin(GL_QUADS);
	switch (control_flag)
	{
	case 0:
		glColor3ub(100, 100, 100);
		break;
	case 1:
		glColor3ub(0, 0, 100);
		break;
	case 2:
		glColor3ub(100, 0, 0);
		break;
	}
	glVertex3f(Plane[0].x, Plane[0].y, Plane[0].z);
	glVertex3f(Plane[1].x, Plane[1].y, Plane[1].z);
	glVertex3f(Plane[2].x, Plane[2].y, Plane[2].z);
	glVertex3f(Plane[3].x, Plane[3].y, Plane[3].z);
	glEnd();

	glBegin(GL_LINES);	
	glColor3ub(0, 0, 255);
	glVertex3f(Upper[0].x, Upper[0].y, Upper[0].z);
	glVertex3f(Upper[1].x, Upper[1].y, Upper[1].z);
	glEnd();

	glLineWidth(20);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(Lower[0].x, Lower[0].y, Lower[0].z);
	glVertex3f(Lower[1].x, Lower[1].y, Lower[1].z);
	glEnd();


	glutSwapBuffers();                
}

static void key(unsigned char key, int x, int y)
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
	case '+':
		if (control_flag < 2)
		{
			control_flag++;
		}
		break;
	case '-':
		if (control_flag > 0)
		{
			control_flag--;
		}
		break;
	}
	glutPostRedisplay();           
}

static void key_release(unsigned char key, int x, int y)
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

	glutPostRedisplay();
}

static void spec(int key, int x, int y) {              
	switch (key) {
	case  GLUT_KEY_UP:
		change_fw = true;
		break;
	case GLUT_KEY_DOWN:
		change_bw = true;
		break;
	case  GLUT_KEY_LEFT:
		change_l = true;
		break;
	case GLUT_KEY_RIGHT:
		change_r = true;
		break;
	}
	glutPostRedisplay();
}

static void specUp(int key, int x, int y) {
	switch (key) {
	case  GLUT_KEY_UP:
		change_fw = false;
		break;
	case GLUT_KEY_DOWN:
		change_bw = false;
		break;
	case  GLUT_KEY_LEFT:
		change_l = false;
		break;
	case GLUT_KEY_RIGHT:
		change_r = false;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);                 
	glutInitWindowPosition(100, 100);              
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("Animation Demo");         
								
	init();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(key_release);
	glutSpecialFunc(spec);
	glutSpecialUpFunc(specUp);
	glutTimerFunc(0, timer, 0);

	glClearColor(0.0, 0.0, 0.0, 1);                 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	GLfloat material[] = { 0.5,0.5,0.5,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);
	glutMainLoop();

	return 0;
}