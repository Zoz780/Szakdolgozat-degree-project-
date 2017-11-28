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
			*Pont t�mb m�ret�nek be�ll�t�sa
	*/
	void SetPointArraySize(int size);

	/**
			*Egy ter�let sz�less�g�nek �s magass�g�nak be�ll�t�sa
	*/
	void SetRange(int value);

	/**
			*K�sz�b�rt�k be�ll�t�sa (Mennyi a max pont egy ter�leten, amely felett m�r feloszt)
	*/
	void SetMaxPointsInArea(int num_of_points);

	/**
			*Node �rt�keinek be�ll�t�sa
	*/
	void SetNode(Node *xy, int x, int y, int w, int h);

	/**
			*N�gyes fa fel�p�t�se
	*/
	void BuildQuadTree(Node *n);

	/**
			*N�gyes fa ki�rat�sa
	*/
	void PrintQuadTree(Node *n, int depth);

	/**
			*N�gyes fa t�rl�se
	*/
	void DeleteQuadTree(Node *n);

private:
	/**
			*Megsz�molja, mennyi pont tal�lhat� egy ter�leten
	*/
	int PointArraySize(Node *n);

	/**
			*Adott Node fel�p�t�se
	*/
	Node *BuildNode(Node *n, Node *nParent, int index);

	int point_array_size;
	int range;
	const int out_of_range = -1; //Ennek �rt�ke mindig -1, ami azt jelenti, hogy a h�l� azon a ponton �res.
	int max_points_in_area;
};

