#include "PathFinder.h"

PathFinder::PathFinder() { }

bool operator<(const Node & a, const Node & b)
{
	return a.GetPriority() > b.GetPriority();
}

void PathFinder::InitMap()
{
	for (int y = 0; y<GRID_SIZE; y++)
	{
		for (int x = 0; x<GRID_SIZE; x++) map[x][y] = 0;
	}

	for (int x = GRID_SIZE / 8; x<GRID_SIZE * 7 / 8; x++)
	{
		map[x][GRID_SIZE / 2] = 1;
	}
	for (int y = GRID_SIZE / 8; y<GRID_SIZE * 7 / 8; y++)
	{
		map[GRID_SIZE / 2][y] = 1;
	}
	for (int x = 16; x<20; x++)
	{
		for (int y = 16; y<20; y++)
		{
			map[x][y] = 1;
		}
	}
}

void PathFinder::SetTheRoute(string route, int xa, int ya)
{
	int j; char c;
	int x = xa;
	int y = ya;
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
}

string PathFinder::PathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish)
{
	priority_queue<Node> pq[2];
	int pqi = 0;
	Node* n0;
	Node* m0;
	int i, j, x, y, xdx, ydy;
	char c;

	for (x = 0; x<GRID_SIZE; x++)
	{
		for (y = 0; y<GRID_SIZE; y++)
		{
			closed_nodes_map[x][y] = 0;
			open_nodes_map[x][y] = 0;
		}
	}

	n0 = new Node(xStart, yStart, 0, 0);
	n0->UpdatePriority(xFinish, yFinish);
	pq[pqi].push(*n0);
	open_nodes_map[x][y] = n0->GetPriority();

	while (!pq[pqi].empty())
	{
		n0 = new Node(pq[pqi].top().GetxPos(), pq[pqi].top().GetyPos(),
			pq[pqi].top().GetLevel(), pq[pqi].top().GetPriority());

		x = n0->GetxPos(); y = n0->GetyPos();

		pq[pqi].pop();
		open_nodes_map[x][y] = 0;
		closed_nodes_map[x][y] = 1;

		if (x == xFinish && y == yFinish)
		{
			string path = "";
			while (!(x == xStart && y == yStart))
			{
				j = direction_map[x][y];
				c = '0' + (j + NUM_OF_DIRECTIONS / 2) % NUM_OF_DIRECTIONS;
				path = c + path;
				x += dx[j];
				y += dy[j];
			}

			delete n0;
			while (!pq[pqi].empty()) pq[pqi].pop();
			return path;
		}

		for (i = 0; i<NUM_OF_DIRECTIONS; i++)
		{
			xdx = x + dx[i]; ydy = y + dy[i];

			if (!(xdx<0 || xdx > GRID_SIZE - 1 || ydy<0 || ydy > GRID_SIZE - 1 || map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1))
			{
				m0 = new Node(xdx, ydy, n0->GetLevel(),
					n0->GetPriority());
				m0->NextLevel(i);
				m0->UpdatePriority(xFinish, yFinish);

				if (open_nodes_map[xdx][ydy] == 0)
				{
					open_nodes_map[xdx][ydy] = m0->GetPriority();
					pq[pqi].push(*m0);
					direction_map[xdx][ydy] = (i + NUM_OF_DIRECTIONS / 2) % NUM_OF_DIRECTIONS;
				}
				else if (open_nodes_map[xdx][ydy]>m0->GetPriority())
				{
					open_nodes_map[xdx][ydy] = m0->GetPriority();
					direction_map[xdx][ydy] = (i + NUM_OF_DIRECTIONS / 2) % NUM_OF_DIRECTIONS;

					while (!(pq[pqi].top().GetxPos() == xdx &&
						pq[pqi].top().GetyPos() == ydy))
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

int PathFinder::GetGridSize() { return GRID_SIZE; }

void PathFinder::Draw(float mul_x, float mul_y)
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (map[i][j] != 0)
			{
				if (map[i][j] == 1)
				{
					glColor3f(0, 0, 0);
				}
				else if (map[i][j] == 2)
				{
					glColor3f(0, 1, 0);
				}
				else if (map[i][j] == 3)
				{
					glColor3f(1, 1, 1);
				}
				else if (map[i][j] == 4)
				{
					glColor3f(1, 0, 0);
				}
				glPointSize(10);
				glBegin(GL_POINTS);
				glVertex2f(10 + (i * mul_x), 10 + (j * mul_y));
				glEnd();

			}
			else
			{
				glColor3f(1, 1, 1);
				glPointSize(1);
				glBegin(GL_POINTS);
				glVertex2f(10 + (i * mul_x), 10 + (j * mul_y));
				glEnd();
			}
		}
	}
}

void PathFinder::Search(int finish_x, int finish_y)
{
	InitMap();

	int xA = 0, yA = 0, xB = finish_x, yB = finish_y;
	cout << "JEOLOLESEK: feher = utvonal, fekete = fal, zold = kezdopont, piros = celpont" << endl;
	cout << "\tTerkep meret (X,Y): " << GRID_SIZE << "," << GRID_SIZE << endl;
	cout << "\tKezdopont koordinata: " << xA << "," << yA << endl;
	cout << "\tCel koordinata: " << xB << "," << yB << endl;

	string route = PathFind(xA, yA, xB, yB);
	if (route == "") cout << "Ures generalt utvonal!" << endl;

	cout << "Utvonal iranyai (0 = jobbra, es novekvo az ora jarasaval megegyezoen):" << endl;
	cout << route << endl << endl;

	if (route.length()>0)
	{
		SetTheRoute(route, xA, yA);
	}
}

Node::Node(int xp, int yp, int d, int p)
{
	position.x = xp; position.y = yp; level = d; priority = p;
}

int Node::GetxPos() const { return position.x; }
int Node::GetyPos() const { return position.y; }
int Node::GetLevel() const { return level; }
int Node::GetPriority() const { return priority; }

void Node::UpdatePriority(const int & xDest, const int & yDest)
{
	priority = level + Estimate(xDest, yDest) * 10;
}

void Node::NextLevel(const int & i)
{
	level += (NUM_OF_DIRECTIONS == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
}

const int &Node::Estimate(const int & xDest, const int & yDest) const
{
	static int xd, yd, d;
	xd = xDest - position.x;
	yd = yDest - position.y;

	d = static_cast<int>(sqrt(xd*xd + yd*yd));

	return(d);
}
