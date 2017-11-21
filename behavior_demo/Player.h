#pragma once
#include "Entity.h"
#include <glut.h>
class Player : public Entity
{
public:
	Player();

	void SetPosX(float x);
	float GetPosX();

	void SetPosY(float y);
	float GetPosY();

	void Draw();

private:

};

