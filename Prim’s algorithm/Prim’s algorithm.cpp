#include<iostream>
#include<vector>
#include<queue>
#include<limits>
#include<utility>
#include<list>
#include<fstream>
#include<cstdlib>
using namespace std;
int width = 6;
int height = 6;
int V = width * height;
vector<int> parent(V, -1);
# define INF 0x3f3f3f3f
typedef pair<int, int> iPair;

class Graph
{
	int V;
	list<pair<int, int>>* k;
public:
	Graph(int V)
	{
		this->V = V;
		k = new list<iPair>[V];
	}
	void addEdge(int u, int v, int w)
	{
		k[u].push_back(make_pair(v, w));
		k[v].push_back(make_pair(u, w));
	}

	
	void MST()
	{
		priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
		
		int src = 0;
		vector<int> key(V, INF);
		
		vector<bool> inMST(V, false);
		
		pq.push(make_pair(0, src));
		key[src] = 0;

		while (!pq.empty())
		{
			int u = pq.top().second;
			pq.pop();
			if (inMST[u]) continue;
			inMST[u] = true;

			for(auto x : k[u]) 
			{
				int v = x.first;
				int weigh = x.second;

				if (!inMST[v] && key[v] > weigh)
				{
					key[v] = weigh;
					pq.push(make_pair(key[v], v));
					parent[v] = u;
				}
			}
		}
		

	}
	
	

	void generateMaze()
	{

		
		vector<vector<char>> maze(height * 2 + 1, vector<char>(width * 2 + 1, '#'));

		for (int i = 0; i < V; i++)
		{
			if (parent[i]!=-1 )
			{
				int u = i;
				int v = parent[i];
				int ux = u % width;
				int uy = u / width;
				int vx = v % width;
				int vy = v / width;

				maze[uy * 2 + 1][ux * 2 + 1] = ' ';
				if (uy == vy)
					maze[uy * 2 + 1][(ux + vx + 1) / 2 * 2] = ' ';
				else
					maze[(uy + vy + 1) / 2 * 2][ux * 2 + 1] = ' ';
				
			}
			
		}

		int side = rand() % 4;
		int entrance, exit;
		switch (side)
		{
		case 0:
			exit = rand() % width;
			maze[height * 2][exit * 2 + 1] = ' '; 
			break;
		case 1: 
			exit = rand() % height;
			maze[exit * 2 + 1][0] = ' '; 
			break;
		case 2: 
			exit = rand() % width;
			maze[0][exit * 2 + 1] = ' '; 
			break;
		case 3:
			exit = rand() % height;
			maze[exit * 2 + 1][width * 2] = ' '; 
			break;
		}

		 side = rand() % 4;
		switch (side)
		{
		case 0:
			entrance = rand() % width;
			maze[0][entrance * 2 + 1] = ' ';
			break;
		case 1:
			entrance = rand() % height;
			maze[entrance * 2 + 1][width * 2] = ' ';
			break;
		case 2:
			entrance = rand() % width;
			maze[height * 2][entrance * 2 + 1] = ' ';
			break;
		case 3:
			entrance = rand() % height;
			maze[entrance * 2 + 1][0] = ' ';
			break;
		}

		maze[1][1] = ' ';
		for (const auto& row : maze)
		{
			for (char cell : row)
				cout << cell;
			cout << endl;
		}
		
		
	}



	void print() {
		cout << "\nStructure:" << endl;
		for (int i = 0; i < V; ++i) {
			cout << "Cell " << i << " is connected to:";
			for (auto it = k[i].begin(); it != k[i].end(); ++it) {
				cout << " " << it->first;
			}
			cout << endl;
		}
	}
};


int main()
{

	Graph g(V);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int u = i * width + j;
			if (i > 0)
				g.addEdge(u, (i - 1) * width + j, rand() % 100);
			if (j > 0)
				g.addEdge(u, i * width + (j - 1), rand() % 100);
		}
	}

	g.MST();
	g.generateMaze();

	return 0;
}

