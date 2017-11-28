#include "QuadTree.h"

QuadTree::QuadTree() { }

void QuadTree::SetPointArraySize(int size) { point_array_size = size; }
void QuadTree::SetRange(int value) { range = value; }
void QuadTree::SetMaxPointsInArea(int num_of_points) { max_points_in_area = num_of_points; }

void QuadTree::SetNode(Node *xy, int x, int y, int w, int h)
{
	int i;
	xy->pointArray = (Point*)malloc(point_array_size * sizeof(Point));
	xy->position.x = x;
	xy->position.y = y;
	xy->length.x = w;
	xy->length.y = h;
	for (i = 0; i<point_array_size; i++)
	{
		xy->pointArray[i].x = out_of_range;
		xy->pointArray[i].y = out_of_range;
	}
	for (int i = 0; i < 4; i++)
		xy->child[i] = nullptr;
}

int QuadTree::PointArraySize(Node *n)
{
	int num_of_valuable_points = 0, i;
	for (i = 0; i <= point_array_size; i++)
		if (n->pointArray[i].x >= 0 && n->pointArray[i].y >= 0)
			num_of_valuable_points++;
	return (num_of_valuable_points + 1);
}

Node *QuadTree::BuildNode(Node *n, Node *nParent, int index)
{
	int numParentPoints, i, j = 0;
	SetNode(n, 0, 0, 0, 0);
	switch (index)
	{
	case 0:
		n->position.x = nParent->position.x + nParent->length.x / 2;
		n->position.y = nParent->position.y + nParent->length.y / 2;
		break;
	case 1:
		n->position.x = nParent->position.x;
		n->position.y = nParent->position.y + nParent->length.y / 2;
		break;
	case 2:
		n->position.x = nParent->position.x;
		n->position.y = nParent->position.y;
		break;
	case 3:
		n->position.x = nParent->position.x + nParent->length.x / 2;
		n->position.y = nParent->position.y;
		break;
	}
	n->length.x = nParent->length.x / 2;
	n->length.y = nParent->length.y / 2;
	n->pointArray = (Point*)malloc(point_array_size * sizeof(Point));

	numParentPoints = PointArraySize(nParent);

	switch (index)
	{
	case 0:
		for (i = 0; i < numParentPoints - 1; i++)
		{
			if (nParent->pointArray[i].x <= range && nParent->pointArray[i].x > nParent->position.x + nParent->length.x / 2 && nParent->pointArray[i].y > nParent->position.y + nParent->length.y / 2 && nParent->pointArray[i].x <= nParent->position.x + nParent->length.x && nParent->pointArray[i].y <= nParent->position.y + nParent->length.y)
			{
				n->pointArray[j].x = nParent->pointArray[i].x;
				n->pointArray[j].y = nParent->pointArray[i].y;
				j++;
			}
		}
		break;
	case 1:
		for (i = 0; i < numParentPoints - 1; i++)
		{
			if (nParent->pointArray[i].x <= range && nParent->pointArray[i].x > nParent->position.x && nParent->pointArray[i].y > nParent->position.y + nParent->length.y / 2 && nParent->pointArray[i].x <= nParent->position.x + nParent->length.x / 2 && nParent->pointArray[i].y <= nParent->position.y + nParent->length.y)
			{
				n->pointArray[j].x = nParent->pointArray[i].x;
				n->pointArray[j].y = nParent->pointArray[i].y;
				j++;
			}
		}
		break;
	case 2:
		for (i = 0; i < numParentPoints - 1; i++)
		{
			if (nParent->pointArray[i].x <= range && nParent->pointArray[i].x > nParent->position.x && nParent->pointArray[i].y > nParent->position.y && nParent->pointArray[i].x <= nParent->position.x + nParent->length.x / 2 && nParent->pointArray[i].y <= nParent->position.y + nParent->length.y / 2)
			{
				n->pointArray[j].x = nParent->pointArray[i].x;
				n->pointArray[j].y = nParent->pointArray[i].y;
				j++;
			}
		}
		break;
	case 3:
		for (i = 0; i < numParentPoints - 1; i++)
		{
			if (nParent->pointArray[i].x <= range && nParent->pointArray[i].x > nParent->position.x + nParent->length.x / 2 && nParent->pointArray[i].y > nParent->position.y && nParent->pointArray[i].x <= nParent->position.x + nParent->length.x && nParent->pointArray[i].y <= nParent->position.y + nParent->length.y / 2)
			{
				n->pointArray[j].x = nParent->pointArray[i].x;
				n->pointArray[j].y = nParent->pointArray[i].y;
				j++;
			}
		}
		break;
	}
	return n;
}

void QuadTree::BuildQuadTree(Node *n)
{
	Node *nodeIn = new Node;
	int points = PointArraySize(n);
	if (points > max_points_in_area)
	{
		for (int k = 0; k < 4; k++)
		{
			n->child[k] = new Node;
			nodeIn = BuildNode(n->child[k], n, k);
			BuildQuadTree(nodeIn);
		}
	}
}

void QuadTree::PrintQuadTree(Node *n, int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "\t";
	if (n->child[0] == nullptr)
	{
		int points = PointArraySize(n);
		cout << "Points: " << points << endl;
		return;
	}
	else if (n->child[0] != nullptr)
	{
		cout << "Children:\n";
		for (int i = 0; i < 4; i++)
			PrintQuadTree(n->child[i], depth + 1);
		return;
	}
}

void QuadTree::DeleteQuadTree(Node *n)
{
	if (n->child[0] == nullptr)
	{
		delete n;
		return;
	}
	else if (n->child[0] != nullptr)
	{
		for (int i = 0; i < 4; i++)
			DeleteQuadTree(n->child[i]);
		return;
	}
}
