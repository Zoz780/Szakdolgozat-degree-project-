#pragma once
#include <iostream>
#include "Waypoint.h"
#include "Vec2.h"
#include <vector>
#include <string>

using namespace std;

class PathFinder
{
public:
	PathFinder();

	/**
			*Waypointok betöltése vektorba
	*/
	void LoadWaypoints();

	/**
			*Kiválasztja az ellenfélhet legközelebb esõ pontot
	*/
	Vec2 SearchClosestWaypoint(float posx, float posy, float *distance);

	/**
			*Kirajzolja a biztonsági pontokat
	*/
	void DrawWaypoints();

private:
	Vec2 m_point_coords[10]; //10 waypoint koordináta
	vector<Waypoint> m_waypoints; //Waypoint-ok vektora

	void SetUpThePointCoords();
};

