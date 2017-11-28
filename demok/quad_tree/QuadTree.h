#pragma once
#include<iostream>
#include<stdlib.h>

using namespace std;

struct Point
{
	int x;
	int y;
};

struct Node
{
	Point position;
	Point length;
	Node *child[4];
	Point *pointArray;
};

class QuadTree
{
public:
	QuadTree();

	/**
			*Pont tömb méretének beállítása
	*/
	void SetPointArraySize(int size);

	/**
			*Egy terület szélességének és magasságának beállítása
	*/
	void SetRange(int value);

	/**
			*Küszöbérték beállítása (Mennyi a max pont egy területen, amely felett már feloszt)
	*/
	void SetMaxPointsInArea(int num_of_points);

	/**
			*Node értékeinek beállítása
	*/
	void SetNode(Node *xy, int x, int y, int w, int h);

	/**
			*Négyes fa felépítése
	*/
	void BuildQuadTree(Node *n);

	/**
			*Négyes fa kiíratása
	*/
	void PrintQuadTree(Node *n, int depth);

	/**
			*Négyes fa törlése
	*/
	void DeleteQuadTree(Node *n);

private:
	/**
			*Megszámolja, mennyi pont található egy területen
	*/
	int PointArraySize(Node *n);

	/**
			*Adott Node felépítése
	*/
	Node *BuildNode(Node *n, Node *nParent, int index);

	int point_array_size;
	int range;
	const int out_of_range = -1; //Ennek értéke mindig -1, ami azt jelenti, hogy a háló azon a ponton üres.
	int max_points_in_area;
};

