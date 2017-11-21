#include "PathFinder.h"

PathFinder::PathFinder()
{

}

void PathFinder::SetUpThePointCoords()
{
	m_point_coords[0].SetX(733); m_point_coords[0].SetY(214);
	m_point_coords[1].SetX(242); m_point_coords[1].SetY(678);
	m_point_coords[2].SetX(650); m_point_coords[2].SetY(487);
	m_point_coords[3].SetX(45); m_point_coords[3].SetY(107);
	m_point_coords[4].SetX(944); m_point_coords[4].SetY(446);
	m_point_coords[5].SetX(1210); m_point_coords[5].SetY(290);
	m_point_coords[6].SetX(1044); m_point_coords[6].SetY(39);
	m_point_coords[7].SetX(170); m_point_coords[7].SetY(176);
	m_point_coords[8].SetX(822); m_point_coords[8].SetY(217);
	m_point_coords[9].SetX(613); m_point_coords[9].SetY(640);
}

void PathFinder::LoadWaypoints()
{
	Waypoint point;
	SetUpThePointCoords();
	for (int i = 0; i < 10; i++)
	{
		point = Waypoint(m_point_coords[i].GetX(), m_point_coords[i].GetY());
		m_waypoints.push_back(point);
	}
	cout << endl;
}

Vec2 PathFinder::SearchClosestWaypoint(float posx, float posy, float *distance)
{
	Waypoint final_point;
	Vec2 closest_point;
	double point_distance = 100000.0, temp;
	double distance_x, distance_y;
	float x, y;
	for (Waypoint& point : m_waypoints)
	{
		x = point.position.GetX();
		y = point.position.GetY();
		distance_x = abs(x - posx);
		distance_y = abs(y - posy);
		temp = sqrtf(distance_x*distance_x + distance_y*distance_y);
		if (temp < point_distance)
		{
			point_distance = temp;
			final_point = point;
		}
	}
	*distance = point_distance;
	closest_point.SetX(final_point.position.GetX());
	closest_point.SetY(final_point.position.GetY());
	return closest_point;
}

void PathFinder::DrawWaypoints()
{
	for (Waypoint& point : m_waypoints)
	{
		point.Draw();
	}
}


