#include "QuadTree.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

QuadTree quadtree;
int point_array_size, range;

/**
		*V�letlenszer� sz�mok gener�l�sa
*/
int RandNum() { return rand() % range; }

/**
		*�rt�kek beolvas�sa a falhaszn�l�t�l
*/
void ReadValuesFromUser()
{
	int max_points_in_area;
	cout << "Irja be, mennyi veletlenszeru pontot szeretne definialni!: ";
	cin >> point_array_size;
	quadtree.SetPointArraySize(point_array_size);

	cout << "\nIrja be a terulet meretet!: ";
	cin >> range;
	quadtree.SetRange(range);

	cout << "\nIrja be, max mennyi pont megengedett egy teruleten!: ";
	cin >> max_points_in_area;
	quadtree.SetMaxPointsInArea(max_points_in_area);
	cout << endl;
}

/**
		*Felhaszn�l�t�l beolvasott �rt�kek alapj�n v�letlenszer� pontok f�jlba �r�sa	
*/
void WritePointsToFile(int *x, int *y)
{
	FILE *file_pointer;
	file_pointer = fopen("valuable_points.txt", "w");

	if (file_pointer == nullptr)
	{
		puts("A filet nem lehet megnyitni!");
		exit(1);
	}
	for (int i = 0; i<point_array_size; i++)
	{
		x[i] = RandNum();  // v�letlenszer� x �rt�k gener�l�s
		y[i] = RandNum();  // v�letlenszer� y �rt�k gerer�l�s
		fprintf(file_pointer, "%d,%d\n", x[i], y[i]);
	}
	fclose(file_pointer);
}
/**
		*V�letlenszer� pontok beolvas�sa f�jlb�l, majd a rootNode-ba �r�sa
*/
void ReadPointsFromFile(Node *root, int *x, int *y)
{
	FILE *file_pointer;
	file_pointer = fopen("valuable_points.txt", "r");
	for (int i = 0; i<point_array_size; i++)
	{
		if (fscanf(file_pointer, "%d,%d", &x[i], &y[i]) != EOF)
		{
			root->pointArray[i].x = x[i];
			root->pointArray[i].y = y[i];
		}
	}
	fclose(file_pointer);
}

int main()
{
	ReadValuesFromUser();

	Node *rootNode = new Node;
	int *x, *y;
	x = (int*)malloc(point_array_size * sizeof(int));
	y = (int*)malloc(point_array_size * sizeof(int));

	quadtree.SetNode(rootNode, 0, 0, range, range);

	WritePointsToFile(x, y);
	ReadPointsFromFile(rootNode, x, y);

	quadtree.BuildQuadTree(rootNode);
	quadtree.PrintQuadTree(rootNode, 0);
	quadtree.DeleteQuadTree(rootNode);

	cout << endl;
	system("pause");
	return 0;
}
