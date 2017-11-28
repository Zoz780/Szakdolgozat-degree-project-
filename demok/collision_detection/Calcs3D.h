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
			*2 vektort tartalmaz� mer�leges vektort ad vissza
	*/
	Vec3 Cross(Vec3 vVector1, Vec3 vVector2);

	/**
			*Kisz�molja a vektort 2 pontb�l
	*/
	Vec3 Vector(Vec3 Point1, Vec3 Point2);

	float Magnitude(Vec3 vNormal);

	/**
			*Norm�liz�lja az �rt�keket
	*/
	Vec3 Normalize(Vec3 vNormal);

	/**
			*Visszaadja a h�romsz�g norm�lvektor�t
	*/
	Vec3 Normal(Vec3 Triangle[]);

	/**
			*Visszaadja, hogy a s�k milyen messze van az orig�t�l (0,0,0).
	*/
	float PlaneDistance(Vec3 vNormal, Vec3 vPoint);

	/**
			*Visszaadja, hogy az egyenes metszi-e a s�kot
	*/
	bool IntersectedPlane(Vec3 vPoly[], Vec3 vLine[], Vec3 &vNormal, float &originDistance);

	/**
			*Visszaadja a k�t vektor metsz�spontj�t
	*/
	float Dot(Vec3 vVector1, Vec3 vVector2);

	/**
			*Visszaadja, a k�t vektor k�zti sz�get
	*/
	double AngleBetweenVectors(Vec3 vVector1, Vec3 vVector2);

	/**
			*Visszaadja, a metsz�spontot
	*/
	Vec3 IntersectionPoint(Vec3 vNormal, Vec3 vLine[], double distance);

	/**
			*Visszaadja, hogy a vonal metsz�spontja benne van-e a h�romsz�gben
	*/
	bool InsideTrinagle(Vec3 vIntersection, Vec3 Poly[], long verticeCount);

	/**
			*Visszaadja, hogy a vonal metszi-e a h�romsz�get.
	*/
	bool IntersectedTriangle(Vec3 vPoly[], Vec3 vLine[], int verticeCount);

};

