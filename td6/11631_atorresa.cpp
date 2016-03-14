#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef vector<pair<unsigned int, long long>> VectLP;
typedef vector<long long> VectL;
typedef vector<bool> VectB;
typedef vector<VectLP> MatLP;

// Get the node with the minimum weight that has not been already visited
int getMinWeight(const VectL &vertexWeight, const VectB &visited)
{
    int min = 0;
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

void bfsWeight(const MatLP &graph, VectL &vertexWeight, VectB &visited, unsigned int &toVisitCount)
{
    while(toVisitCount)
    {
        unsigned int toVisit = getMinWeight(vertexWeight, visited);
        visited[toVisit] = true;
        --toVisitCount;

	// Browse th graph and adding the weight to the nodes if it is better
        for(unsigned int i = 0; i < graph[toVisit].size(); ++i)
        {
            if(!visited[graph[toVisit][i].first] && (vertexWeight[graph[toVisit][i].first] == -1 || vertexWeight[graph[toVisit][i].first] > graph[toVisit][i].second))
                vertexWeight[graph[toVisit][i].first] = graph[toVisit][i].second;
        }        
    }
} 

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int vertexCount;
    unsigned int edgesCount;

    while(cin >> vertexCount)
    {
	
        cin >> edgesCount;
        if(edgesCount == vertexCount && vertexCount == 0)
            return 0;

        // Create the matrix with weight information (-1 if not connected)
        MatLP graph(vertexCount, VectLP());
        VectL vertexWeight(vertexCount, -1);
        VectB visited(vertexCount, 0);

        for(unsigned int i = 0 ; i < vertexCount; ++i)
            graph[i].push_back(make_pair(i, 0));
        

        long long maxPrice = 0;

        unsigned int cpt = edgesCount;
        while(edgesCount)
        {
            unsigned int x;
            unsigned int y;
            unsigned int z;
            cin >> x;
            cin >> y;
            cin >> z;
            graph[x].push_back(make_pair(y, z));
            graph[y].push_back(make_pair(x, z));
            maxPrice += z;
            --edgesCount;
        }

        vertexWeight[0] = 0;
        unsigned int toVisitCount = vertexCount;

	// We get the minimum covering tree
        bfsWeight(graph, vertexWeight, visited, toVisitCount);

        for(unsigned int i = 0; i < vertexCount; ++i)
        {        
            maxPrice -= vertexWeight[i];
        }

        cout << maxPrice << endl;
     
    }
    return 0;
} // main()
