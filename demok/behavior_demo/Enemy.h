#pragma once
#include "Entity.h"
#include "PathFinder.h"
#include "Vec2.h"
#include <glut.h>

class Characteristics
{
public:
	float fear; //az ellenf�l f�lelme, amely a k�k (biztons�gi) pontokhoz val� visszat�r�s sugar�t �ll�tja
	float speed; //az ellenf�l sebess�ge
};

class Enemy : public Entity
{
public:
	Enemy();

	/**
			*C�lpont be�ll�t�sa
	*/
	void SetDestinaiton(float x, float y, bool flag);

	/**
			*Ellenf�l mozgat�sa a c�lig
	*/
	void MoveToDestination(double elapsed_time);

	/**
			*Ellenf�l tulajdons�gainak be�ll�t�sa
	*/
	void SetCharacteristics(float fear, float speed);

	/**
			*Figyeli az ellenfelet, hogy mikor �r a j�t�koshoz
	*/
	bool SetRoundEnd(float x, float y);

	void SetPosX(float x);
	float GetPosX();

	void SetPosY(float y);
	float GetPosY();

	/**
			*Az ellenf�l f�lelme l�that� legyen, vagy nem
	*/
	void ChangeFearCircleVisibility();

	/**
			*Ellenf�l rajzol�sa
	*/
	void Draw();

private:
	Characteristics character; //karakterisztika
	Vec2 destination; //c�l
	PathFinder pathfinder;
	GLUquadric *fear_radius;

	bool is_visible_fear;
};

