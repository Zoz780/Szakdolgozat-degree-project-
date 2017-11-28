#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include "Vec3.h"

#include <iostream>
using namespace std;

class Calcs3D
{
public:
	Calcs3D();
	
	/**
			*2 vektort tartalmazó merõleges vektort ad vissza
	*/
	Vec3 Cross(Vec3 vVector1, Vec3 vVector2);

	/**
			*Kiszámolja a vektort 2 pontból
	*/
	Vec3 Vector(Vec3 Point1, Vec3 Point2);

	float Magnitude(Vec3 vNormal);

	/**
			*Normálizálja az értékeket
	*/
	Vec3 Normalize(Vec3 vNormal);

	/**
			*Visszaadja a háromszög normálvektorát
	*/
	Vec3 Normal(Vec3 Triangle[]);

	/**
			*Visszaadja, hogy a sík milyen messze van az origótól (0,0,0).
	*/
	float PlaneDistance(Vec3 vNormal, Vec3 vPoint);

	/**
			*Visszaadja, hogy az egyenes metszi-e a síkot
	*/
	bool IntersectedPlane(Vec3 vPoly[], Vec3 vLine[], Vec3 &vNormal, float &originDistance);

	/**
			*Visszaadja a két vektor metszéspontját
	*/
	float Dot(Vec3 vVector1, Vec3 vVector2);

	/**
			*Visszaadja, a két vektor közti szöget
	*/
	double AngleBetweenVectors(Vec3 vVector1, Vec3 vVector2);

	/**
			*Visszaadja, a metszéspontot
	*/
	Vec3 IntersectionPoint(Vec3 vNormal, Vec3 vLine[], double distance);

	/**
			*Visszaadja, hogy a vonal metszéspontja benne van-e a háromszögben
	*/
	bool InsideTrinagle(Vec3 vIntersection, Vec3 Poly[], long verticeCount);

	/**
			*Visszaadja, hogy a vonal metszi-e a háromszöget.
	*/
	bool IntersectedTriangle(Vec3 vPoly[], Vec3 vLine[], int verticeCount);

};

