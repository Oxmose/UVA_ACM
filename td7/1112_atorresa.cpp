#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

#define MatI vector<vector<int>>
#define VecB vector<bool>
#define VecL vector<long long>
#define VecI vector<int>

using namespace std;

int getMinDist(const VecL &dists, const VecB &visited)
{
	long long min = LLONG_MAX;
	int vertex = -1;
	for(unsigned int i = 0; i < dists.size(); ++i)
	{
		if(!visited[i] && dists[i] < min)
		{
			min = dists[i];
			vertex = i;
		}
	}
	return vertex;
}

void dijkstra(const MatI &graph, const unsigned int &nodeEnd, VecL &dists)
{
    // Init
    VecB visited(dists.size(), false);
    dists[nodeEnd] = 0;

    // Browse
    unsigned int toVisit = dists.size();

    while(toVisit)
    {
        int nextVisit = getMinDist(dists, visited);
        if(nextVisit == -1)
            return;

        visited[nextVisit] = true;
        --toVisit;

        for(unsigned int i = 0; i < graph[nextVisit].size(); ++i)
        {
            if(graph[nextVisit][i] != -1)
            {
                if(dists[i] > (dists[nextVisit] + graph[nextVisit][i]))
                    dists[i] = dists[nextVisit] + graph[nextVisit][i];
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);

    bool fst = true;
	unsigned int buff;
	cin >> buff;
	unsigned int cellsCount;
	while(cin >> cellsCount)
	{
		if(fst)
		{
			fst = false;
		}
		else
		{
			cout << endl;
		}
		unsigned int exit;
		unsigned int timer;

		cin >> exit >> timer;
		--exit;
		MatI graph(cellsCount, VecI(cellsCount, -1));

		unsigned int edges;
		cin >> edges;

		unsigned int x;
		unsigned int y;

		for(unsigned int i = 0; i < edges; ++i)
		{
			cin >> x >> y;
			// Make the G-1 graph in order to apply Dijkstra on the end node
			cin >> graph[y - 1][x - 1];
		}

		// For all mices get the shortest path
		unsigned int miceOut = 0;
		VecL dists(cellsCount, LLONG_MAX);

		dijkstra(graph, exit, dists);

		for(unsigned int i = 0; i < dists.size(); ++i)
			if(timer >= dists[i] && dists[i] != LLONG_MAX)
				++miceOut;

		cout << miceOut << endl;
	}
	return 0;
} // main()
