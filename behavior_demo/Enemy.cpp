#include "Enemy.h"

Enemy::Enemy()
{
	position.SetX(5);
	position.SetY(5);
	pathfinder.LoadWaypoints();
}

void Enemy::SetDestinaiton(float x, float y, bool flag)
{
	Vec2 goal;
	float distance;
	if (!flag)
	{
		destination.SetX(x);
		destination.SetY(y);
	}
	else
	{
		goal = pathfinder.SearchClosestWaypoint(position.GetX(), position.GetY(), &distance);
		if (distance >= character.fear)
		{
			destination.SetX(x);
			destination.SetY(y);
		}
		else
		{
			destination.SetX(goal.GetX());
			destination.SetY(goal.GetY());
		}
	}
}

bool Enemy::SetRoundEnd(float x, float y)
{
	const float player_radius = 10.0f;
	if ((abs(x - position.GetX()) < player_radius) && (abs(y - position.GetY()) < player_radius))
	{
		return false;
	}
	else
		return true;
}

void Enemy::MoveToDestination(double elapsed_time)
{
	Vec2 diff;

	diff.SetX(destination.GetX() - position.GetX());
	diff.SetY(destination.GetY() - position.GetY());

	if (diff.GetLength() == 0)        
		return;

	const float speed = character.speed;       

	diff.SetMagnitude((speed * elapsed_time) * 25);

	float x = position.GetX();
	float y = position.GetY();

	x += diff.GetX();
	y += diff.GetY();

	position.SetX(x);
	position.SetY(y);
}

void Enemy::SetCharacteristics(float fear, float speed)
{
	character.fear = fear;
	character.speed = speed;
}

void Enemy::SetPosX(float x)
{
	position.SetX(x);
}

float Enemy::GetPosX()
{
	return position.GetX();
}

void Enemy::SetPosY(float y)
{
	position.SetY(y);
}

float Enemy::GetPosY()
{
	return position.GetY();
}

void Enemy::Draw()
{
	pathfinder.DrawWaypoints();

	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex2f(position.GetX(), position.GetY());
	glEnd();
}