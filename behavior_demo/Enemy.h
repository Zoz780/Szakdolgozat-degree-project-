#pragma once
#include "Entity.h"
#include "PathFinder.h"
#include "Vec2.h"
#include <glut.h>

class Characteristics
{
public:
	float fear;
	float speed;
};

class Enemy : public Entity
{
public:
	Enemy();

	void SetDestinaiton(float x, float y, bool flag);

	void MoveToDestination(double elapsed_time);

	void SetCharacteristics(float fear, float speed);

	bool SetRoundEnd(float x, float y);

	void SetPosX(float x);
	float GetPosX();

	void SetPosY(float y);
	float GetPosY();

	void Draw();

private:
	Characteristics character;
	Vec2 destination;
	PathFinder pathfinder;
};

