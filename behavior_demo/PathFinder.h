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
	void LoadWaypoints();
	Vec2 SearchClosestWaypoint(float posx, float posy, float *distance);
	void DrawWaypoints();

private:
	Vec2 m_point_coords[10];
	vector<Waypoint> m_waypoints;
	vector<pair<Waypoint*, Waypoint*>> m_graph;

	void SetUpThePointCoords();
};

