#pragma once
#include "Entity.h"
#include "PathFinder.h"
#include "Vec2.h"
#include <glut.h>

class Characteristics
{
public:
	float fear; //az ellenfél félelme, amely a kék (biztonsági) pontokhoz való visszatérés sugarát állítja
	float speed; //az ellenfél sebessége
};

class Enemy : public Entity
{
public:
	Enemy();

	/**
			*Célpont beállítása
	*/
	void SetDestinaiton(float x, float y, bool flag);

	/**
			*Ellenfél mozgatása a célig
	*/
	void MoveToDestination(double elapsed_time);

	/**
			*Ellenfél tulajdonságainak beállítása
	*/
	void SetCharacteristics(float fear, float speed);

	/**
			*Figyeli az ellenfelet, hogy mikor ér a játékoshoz
	*/
	bool SetRoundEnd(float x, float y);

	void SetPosX(float x);
	float GetPosX();

	void SetPosY(float y);
	float GetPosY();

	/**
			*Az ellenfél félelme látható legyen, vagy nem
	*/
	void ChangeFearCircleVisibility();

	/**
			*Ellenfél rajzolása
	*/
	void Draw();

private:
	Characteristics character; //karakterisztika
	Vec2 destination; //cél
	PathFinder pathfinder;
	GLUquadric *fear_radius;

	bool is_visible_fear;
};

