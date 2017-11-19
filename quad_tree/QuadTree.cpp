#include<stdio.h>
#include<stdlib.h>

struct Point
{
		int x;
		int y;
};

struct Node	
{	
		int posX;
		int posY;
		int width;
		int height;
		Node *child[4];
		Point pointArray[5000];
};

void BuildQuadTree(Node *n);
void PrintQuadTree(Node *n, int depth = 0);
void DeleteQuadTree(Node *n);
Node *BuildNode(Node *n, Node  *nParent, int index);

void SetNode(Node *xy, int x, int y, int w, int h)
{
		int i;
		xy->posX = x;
		xy->posY = y;
		xy->width = w;
		xy->height = h;
		for (i = 0; i<5000; i++)
		{
				xy->pointArray[i].x = 560;
				xy->pointArray[i].y = 560;
		}
		for (int i = 0; i < 4; i++)
			xy->child[i] = NULL;
}
int RandNum()
{
		int a;
		a = rand() % 100;
		return a;
}

int PointArraySize(Node *n)
{
		int m = 0, i;
		for (i = 0; i <= 5000; i++)
			if (n->pointArray[i].x <= 500 && n->pointArray[i].y <= 500)
				m++;
		return (m + 1);
}

void BuildQuadTree(Node *n)
{
		Node * nodeIn = new Node;
		int points = PointArraySize(n);
		if (points > 100)
		{
				for (int k = 0; k < 4; k++)
				{
						n->child[k] = new Node;
						nodeIn = BuildNode(n->child[k], n, k);
						BuildQuadTree(nodeIn);
				}
		}
}

void PrintQuadTree(Node *n, int depth)
{
		for (int i = 0; i < depth; i++)
			printf("\t");
		if (n->child[0] == NULL)
		{
				int points = PointArraySize(n);
				printf("Points: %d\n", points);
				return;
		}
		else if (n->child[0] != NULL)
		{
				printf("Children:\n");
				for (int i = 0; i < 4; i++)
					PrintQuadTree(n->child[i], depth + 1);
				return;
		}
}

void DeleteQuadTree(Node *n)
{
		if (n->child[0] == NULL)
		{
				delete n;
				return;
		}
		else if (n->child[0] != NULL)
		{
				for (int i = 0; i < 4; i++)
					DeleteQuadTree(n->child[i]);
				return;
		}
}

Node *BuildNode(Node *n, Node *nParent, int index)
{
		int numParentPoints, i, j = 0;
		SetNode(n, 0, 0, 0, 0);
		switch (index)
		{
		case 0:
				n->posX = nParent->posX + nParent->width / 2;
				n->posY = nParent->posY + nParent->height / 2;
				break;
		case 1:
				n->posX = nParent->posX;
				n->posY = nParent->posY + nParent->height / 2;
				break;
		case 2:
				n->posX = nParent->posX;
				n->posY = nParent->posY;
				break;
		case 3:
				n->posX = nParent->posX + nParent->width / 2;
				n->posY = nParent->posY;
				break;
		}
		n->width = nParent->width / 2;
		n->height = nParent->height / 2;

		numParentPoints = PointArraySize(nParent);

		switch (index)
		{
		case 0:
				for (i = 0; i < numParentPoints - 1; i++)
				{
						if (nParent->pointArray[i].x <= 500 && nParent->pointArray[i].x > nParent->posX + nParent->width / 2 && nParent->pointArray[i].y > nParent->posY + nParent->height / 2 && nParent->pointArray[i].x <= nParent->posX + nParent->width && nParent->pointArray[i].y <= nParent->posY + nParent->height)
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
						if (nParent->pointArray[i].x <= 500 && nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY + nParent->height / 2 && nParent->pointArray[i].x <= nParent->posX + nParent->width / 2 && nParent->pointArray[i].y <= nParent->posY + nParent->height)
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
						if (nParent->pointArray[i].x <= 500 && nParent->pointArray[i].x > nParent->posX && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->width / 2 && nParent->pointArray[i].y <= nParent->posY + nParent->height / 2)
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
						if (nParent->pointArray[i].x <= 500 && nParent->pointArray[i].x > nParent->posX + nParent->width / 2 && nParent->pointArray[i].y > nParent->posY && nParent->pointArray[i].x <= nParent->posX + nParent->width && nParent->pointArray[i].y <= nParent->posY + nParent->height / 2)
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

int main()
{
	Node * rootNode = new Node;
	int i, x[5000], y[5000];
	FILE *fp;
	SetNode(rootNode, 0, 0, 500, 500);

	fp = fopen("output.txt", "w");

	if (fp == NULL)
	{
		puts("Cannot open file");
		exit(1);
	}
	for (i = 0; i<5000; i++)
	{
		x[i] = RandNum();
		y[i] = RandNum();
		fprintf(fp, "%d,%d\n", x[i], y[i]);
	}
	fclose(fp);

	fp = fopen("output.txt", "r");
	for (i = 0; i<5000; i++)
	{
		if (fscanf(fp, "%d,%d", &x[i], &y[i]) != EOF)
		{
			rootNode->pointArray[i].x = x[i];
			rootNode->pointArray[i].y = y[i];
		}
	}

	fclose(fp);

	BuildQuadTree(rootNode);
	PrintQuadTree(rootNode);
	DeleteQuadTree(rootNode);
	getchar();
	return 0;
}
