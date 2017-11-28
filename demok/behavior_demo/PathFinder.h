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
			*Waypointok bet�lt�se vektorba
	*/
	void LoadWaypoints();

	/**
			*Kiv�lasztja az ellenf�lhet legk�zelebb es� pontot
	*/
	Vec2 SearchClosestWaypoint(float posx, float posy, float *distance);

	/**
			*Kirajzolja a biztons�gi pontokat
	*/
	void DrawWaypoints();

private:
	Vec2 m_point_coords[10]; //10 waypoint koordin�ta
	vector<Waypoint> m_waypoints; //Waypoint-ok vektora

	void SetUpThePointCoords();
};

