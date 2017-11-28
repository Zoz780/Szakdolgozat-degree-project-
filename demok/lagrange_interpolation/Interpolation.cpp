#include <iostream>
#include <GLUT.h>
using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

float *x, *y, *results_x , *results_y;
float min_x_value, max_x_value, min_y_value, max_y_value;
float multiply_x, multiply_y;
float dynamic_width, dynamic_height;
int number_of_pairs;

/**
		*Lagrange interpoláció implementációja
*/
bool LagrangeInterpolation(float x[], float y[], int num, float in, float *result)
{
	float s = 1, t = 1;
	for (int i = 0; i<num; i++)
	{
		s = 1;
		t = 1;
		for (int j = 0; j<num; j++)
		{
			if (j != i)
			{
				s = s*(in - x[j]);
				t = t*(x[i] - x[j]);
			}
		}
		*result += ((s / t)*y[i]);
	}
	return true;
}


/**
		*Értékbekérés a felhasználótól
*/
bool ValuesReader()
{
	float input, result = 0;
	int i, j, isContinue = 1;
		cout << "Adja meg mennyi x es y erteket szeretne beirni: ";
		cin >> number_of_pairs;
		if (number_of_pairs == 0)
		{
			return false;
		}
		else
		{
			x = (float *)malloc(number_of_pairs * sizeof(float));
			y = (float *)malloc(number_of_pairs * sizeof(float));
		}
		cout << "Irja be az x es y ertekeket (x>0): \n";
		for (i = 0; i<number_of_pairs; i++)
		{
			cin >> x[i];
			cin >> y[i];
		}
		cout << "A bevitt ertekek a kovetkezok: \n";
		for (i = 0; i<number_of_pairs; i++)
		{
			cout << x[i] << "\t" << y[i] << endl;
		}
		min_x_value = x[0];
		max_x_value = x[0];
		int max_index = 0;
		for (int i = 0; i < number_of_pairs; i++)
		{
			if (x[i] > max_x_value)
			{
				max_x_value = x[i];
				max_index = i;
			}
			if (x[i] < min_x_value)
			{
				min_x_value = x[i];
			}
		}

		results_x = (float *)malloc((max_x_value - min_x_value + 1) * sizeof(float));
		results_y = (float *)malloc((max_x_value - min_x_value + 1) * sizeof(float));


		int index = 0;
		for (int i = x[0]; i <= x[max_index]; i++)
		{
			result = 0;
			LagrangeInterpolation(x, y, number_of_pairs, i, &result);
			results_x[index] = i;
			results_y[index] = result;
			cout << "\nAhol x = " << results_x[index] << ", a hozza tartozo y ertek: " << results_y[index];
			index++;
		}
		cout << endl;

		min_y_value = results_y[0];
		max_y_value = results_y[0];
		for (int i = 0; i < max_x_value; i++)
		{
			if ((results_y[i] > max_y_value) && (results_y[i] <= 10000.0f))
			{
				max_y_value = results_y[i];
			}
		}
		for (int i = 0; i < max_x_value; i++)
		{
			if ((results_y[i] < min_y_value) && (results_y[i] >= -10000.0f))
			{
				min_y_value = results_y[i];
			}
		}
	return true;
}

/**
		*Értékek felskálázása az adott ablak felbontásához
*/
void CalcLimits(int width, int height)
{
	if (max_y_value > abs(min_y_value))
	{
		min_y_value = max_y_value;
	}
	else min_y_value = abs(min_y_value);

	multiply_x = (width / max_x_value) * 0.98; //Szorozva 0.98-al, hogy ne pont az ablak szélére essen a függvény vége
	multiply_y = ((height / 2) / min_y_value) * 0.98; //Szorozva 0.98-al, hogy ne pont az ablak szélére essen a függvény vége
}

/**
		*Ablak méretezése
*/
static void resize(int width, int height)    
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	dynamic_width = width;
	dynamic_height = height;
	CalcLimits(width, height);
}

/**
		*Függvény rajzolása OpenGL-el
*/
static void display(void)                
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	
	glLineWidth(1);
	glColor3f(1, 1, 1);

	glBegin(GL_LINES);
	glVertex2f(0, dynamic_height / 2);
	glVertex2f(dynamic_width, dynamic_height / 2);
	glEnd();

	if (multiply_x > 9.0)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x3F07);
		for (float i = 0; i < (float)dynamic_width; i += multiply_x)
		{
			glColor3f(0.7, 0.7, 0.7);
			glBegin(GL_LINES);
			glVertex2f(i, 0);
			glVertex2f(i, dynamic_height);
			glEnd();
		}
		glDisable(GL_LINE_STIPPLE);
	}
	glLineWidth(2);
	glColor3f(1, 1, 1);

	if (number_of_pairs == 1)
	{
		glPointSize(2);
		for (int i = 0; i < dynamic_width; i++)
		{
			glBegin(GL_LINES);
			glVertex2f((i * multiply_x), (dynamic_height / 2) - (results_y[0] * multiply_y));
			glVertex2f(((i+1) * multiply_x), (dynamic_height / 2) - (results_y[0] * multiply_y));
			glEnd();
		}
	}
	else
	{
		for (int i = 0; i < max_x_value - min_x_value; i++)
		{
			glBegin(GL_LINES);
			glVertex2f((results_x[i] * multiply_x), (dynamic_height / 2) - (results_y[i] * multiply_y));
			glVertex2f((results_x[i + 1] * multiply_x), (dynamic_height / 2) - (results_y[i + 1] * multiply_y));
			glEnd();
		}
	}
	cout << "\nAz X ertekek szorzoja: " << multiply_x << endl;
	glutSwapBuffers();                
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(0, 0);              
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("Lagrange Interpolation Demo");         
							
	glutReshapeFunc(resize);
	if (!ValuesReader())
	{
		return 0;
	}
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}