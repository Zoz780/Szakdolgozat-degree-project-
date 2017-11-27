#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

const int n = 48; 
const int m = 48; 
static int map[n][m];
static int closed_nodes_map[n][m]; 
static int open_nodes_map[n][m]; 
static int dir_map[n][m]; 
const int dir = 8; 
static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 };
static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 };

class Node
{
	int xPos;
	int yPos;
	int level;
	int priority; 

public:
	Node(int xp, int yp, int d, int p)
	{
		xPos = xp; yPos = yp; level = d; priority = p;
	}

	int getxPos() const { return xPos; }
	int getyPos() const { return yPos; }
	int getLevel() const { return level; }
	int getPriority() const { return priority; }

	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10; 
	}

	void nextLevel(const int & i)
	{
		level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}

	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;

		d = static_cast<int>(sqrt(xd*xd + yd*yd));

		return(d);
	}
};

bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

string pathFind(const int & xStart, const int & yStart,
	const int & xFinish, const int & yFinish)
{
	static priority_queue<Node> pq[2]; 
	static int pqi; 
	static Node* n0;
	static Node* m0;
	static int i, j, x, y, xdx, ydy;
	static char c;
	pqi = 0;

	for (y = 0; y<m; y++)
	{
		for (x = 0; x<n; x++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	n0 = new Node(xStart, yStart, 0, 0);
	n0->updatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->getPriority();

	while (!pq[pqi].empty())
	{
		n0 = new Node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
			pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

		x = n0->getxPos(); y = n0->getyPos();

		pq[pqi].pop(); 
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;

		if (x == xFinish && y == yFinish)
		{
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = dir_map[x][y];
				c = '0' + (j + dir / 2) % dir;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			delete n0;
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		for (i = 0; i<dir; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx>n - 1 || ydy<0 || ydy>m - 1 || map[xdx][ydy] == 1
				|| closed_nodes_map[xdx][ydy] == 1))
			{
				m0 = new Node(xdx, ydy, n0->getLevel(),
					n0->getPriority());
				m0->nextLevel(i);
				m0->updatePriority(xFinish, yFinish);

				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					pq[pqi].push(*m0);
					dir_map[xdx][ydy] = (i + dir / 2) % dir;
				}
				else if (open_nodes_map[xdx][ydy]>m0->getPriority())
				{
					open_nodes_map[xdx][ydy] = m0->getPriority();
					dir_map[xdx][ydy] = (i + dir / 2) % dir;

					while (!(pq[pqi].top().getxPos() == xdx &&
						pq[pqi].top().getyPos() == ydy))
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pq[pqi].pop();

					if (pq[pqi].size()>pq[1 - pqi].size()) pqi = 1 - pqi;
					while (!pq[pqi].empty())
					{
						pq[1 - pqi].push(pq[pqi].top());
						pq[pqi].pop();
					}
					pqi = 1 - pqi;
					pq[pqi].push(*m0);
				}
				else delete m0;
			}
		}
		delete n0;
	}
	return "";
}

int main(void)
{
	srand(time(NULL));

	for (int y = 0; y<m; y++)
	{
		for (int x = 0; x<n; x++) map[x][y] = 0;
	}

	for (int x = n / 8; x<n * 7 / 8; x++)
	{
		map[x][m / 2] = 1;
	}
	for (int y = m / 8; y<m * 7 / 8; y++)
	{
		map[n / 2][y] = 1;
	}

	//fillout more walls
	for (int x = 30; x<40; x++)
	{
		for (int y = 30; y<40; y++)
		{
			map[x][y] = 1;
		}
	}

	int xA = 0, yA = 0, xB = n - 1, yB = m - 1;

	cout << "Map Size (X,Y): " << n << "," << m << endl;
	cout << "Start: " << xA << "," << yA << endl;
	cout << "Finish: " << xB << "," << yB << endl;
	clock_t start = clock();
	string route = pathFind(xA, yA, xB, yB);
	if (route == "") cout << "An empty route generated!" << endl;
	clock_t end = clock();
	double time_elapsed = double(end - start);
	cout << "Time to calculate the route (ms): " << time_elapsed << endl;
	cout << "Route:" << endl;
	cout << route << endl << endl;

	if (route.length()>0)
	{
		int j; char c;
		int x = xA;
		int y = yA;
		map[x][y] = 2;
		for (int i = 0; i<route.length(); i++)
		{
			c = route.at(i);
			j = atoi(&c);
			x = x + dx[j];
			y = y + dy[j];
			map[x][y] = 3;
		}
		map[x][y] = 4;

		for (int y = 0; y<m; y++)
		{
			for (int x = 0; x<n; x++)
				if (map[x][y] == 0)
					cout << " . ";
				else if (map[x][y] == 1)
					cout << " O "; 
				else if (map[x][y] == 2)
					cout << " S "; 
				else if (map[x][y] == 3)
					cout << " R ";
				else if (map[x][y] == 4)
					cout << " F "; 
			cout << endl;
		}
	}
	getchar(); 
	return(0);
}