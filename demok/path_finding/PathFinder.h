#pragma once
#include "Vec2.h"
#include <iostream>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <GLUT.h>
#include <stdlib.h>
using namespace std;

#define GRID_SIZE 24
#define NUM_OF_DIRECTIONS 8

class Node
{
	Vec2 position;
	int level;
	int priority;  //Adott Node prioritása A* szabály alapján

public:
	Node(int xp, int yp, int d, int p);

	int GetxPos() const;
	int GetyPos() const;
	int GetLevel() const;
	int GetPriority() const;

	/**
			*Prioritás frissítése
	*/
	void UpdatePriority(const int & xDest, const int & yDest);

	/**
			*A függõleges és vízszintes irány elõnyben részesítése az átlóssal szemben
	*/
	void NextLevel(const int & i);

	/**
			*Hátralévõ távolság a célig
	*/
	const int &Estimate(const int & xDest, const int & yDest) const;
};

class PathFinder
{
public:
	PathFinder();

	/**
			*Útvonalszámítás indítása
	*/
	void Search(int finish_x, int finish_y);

	/**
			*Útvonal és a falak kirajzolása OpenGL segítségével
	*/
	void Draw(float mul_x, float mul_y);

	/**
			*Visszaadja a pontháló méretét
	*/
	int GetGridSize();

private:
	/**
			*Minden érték kinullázása, illetve falak beállítása a ponthálón
	*/
	void InitMap();

	/**
			*Az útvonal ponthálóba írása az útvonalszámító string eredménye alapján
	*/
	void SetTheRoute(string route, int xa, int ya);
	string PathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish);

	int map[GRID_SIZE][GRID_SIZE];
	int closed_nodes_map[GRID_SIZE][GRID_SIZE];
	int open_nodes_map[GRID_SIZE][GRID_SIZE];
	int direction_map[GRID_SIZE][GRID_SIZE];
	int dx[NUM_OF_DIRECTIONS] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int dy[NUM_OF_DIRECTIONS] = { 0, 1, 1, 1, 0, -1, -1, -1 };
};

