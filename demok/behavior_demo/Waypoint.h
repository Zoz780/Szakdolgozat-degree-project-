#pragma once
#include "Vec2.h"
#include <glut.h>

enum class WaypointType
{
	SIMPLE
};

class Waypoint
{
public:
	Waypoint();
	Waypoint(int x, int y);
	Vec2 position;
	WaypointType type;
	
	/**
			*Waypoint rajzolása
	*/
	void Draw();
};

