#include "Player.h"



Player::Player()
{
	position.SetX(100);
	position.SetY(100);
}

void Player::SetPosX(float x)
{
	position.SetX(x);
}

float Player::GetPosX()
{
	return position.GetX();
}

void Player::SetPosY(float y)
{
	position.SetY(y);
}

float Player::GetPosY()
{
	return position.GetY();
}

void Player::Draw()
{
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex2f(position.GetX(), position.GetY());
	glEnd();
}
