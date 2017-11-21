#include "Waypoint.h"

Waypoint::Waypoint()
{

}

Waypoint::Waypoint(int x, int y)
{
	position.SetX(x);
	position.SetY(y);
}

void Waypoint::Draw()
{
	glPointSize(8);
	glColor3f(0, 0.5, 1);
	glBegin(GL_POINTS);
	glVertex2f(position.GetX(), position.GetY());
	glEnd();
}


