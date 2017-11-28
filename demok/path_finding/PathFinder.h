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
	int priority;  //Adott Node priorit�sa A* szab�ly alapj�n

public:
	Node(int xp, int yp, int d, int p);

	int GetxPos() const;
	int GetyPos() const;
	int GetLevel() const;
	int GetPriority() const;

	/**
			*Priorit�s friss�t�se
	*/
	void UpdatePriority(const int & xDest, const int & yDest);

	/**
			*A f�gg�leges �s v�zszintes ir�ny el�nyben r�szes�t�se az �tl�ssal szemben
	*/
	void NextLevel(const int & i);

	/**
			*H�tral�v� t�vols�g a c�lig
	*/
	const int &Estimate(const int & xDest, const int & yDest) const;
};

class PathFinder
{
public:
	PathFinder();

	/**
			*�tvonalsz�m�t�s ind�t�sa
	*/
	void Search(int finish_x, int finish_y);

	/**
			*�tvonal �s a falak kirajzol�sa OpenGL seg�ts�g�vel
	*/
	void Draw(float mul_x, float mul_y);

	/**
			*Visszaadja a ponth�l� m�ret�t
	*/
	int GetGridSize();

private:
	/**
			*Minden �rt�k kinull�z�sa, illetve falak be�ll�t�sa a ponth�l�n
	*/
	void InitMap();

	/**
			*Az �tvonal ponth�l�ba �r�sa az �tvonalsz�m�t� string eredm�nye alapj�n
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

