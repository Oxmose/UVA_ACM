#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

#define MatI vector<vector<int>>
#define VecB vector<bool>
#define VecI vector<int>

// Get the node with the minimum weight that has not been already visited
int getMinDist(const VecI &vertexWeight, const VecB &visited)
{
    unsigned int min = 0;
    unsigned int vertice = -1;
    bool assigned = false;
    for(unsigned int i = 0; i < vertexWeight.size(); ++i)
    {
	    // If we never assigned weight to the node
        if(!visited[i] && !assigned && vertexWeight[i] > -1)
        {
            assigned = true;
            min = vertexWeight[i];
            vertice = i;
        }
        else if(!visited[i] && vertexWeight[i] > -1 && vertexWeight[i] < min)
        {
            min = vertexWeight[i];
            vertice = i;
        }
    }
    return vertice;
}

void dijkstra(const MatI &graph, const unsigned int &nodeEnd, VecI &dists)
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
                if(dists[i] == -1 || dists[i] > (dists[nextVisit] + graph[nextVisit][i]))
                    dists[i] = dists[nextVisit] + graph[nextVisit][i];
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int buff;
    cin >> buff;
    unsigned int cellsCount;
    while(cin >> cellsCount)
    {
	    
        unsigned int exit;
        unsigned int timer;

        cin >> exit >> timer;
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
        VecI dists(cellsCount, -1);

        dijkstra(graph, exit, dists);

        for(unsigned int i = 0; i < cellsCount; ++i)
            if(timer >= dists[i] && dists[i] != -1)
                ++miceOut;

        cout << miceOut << endl << endl;     
    }
    return 0;
} // main()
