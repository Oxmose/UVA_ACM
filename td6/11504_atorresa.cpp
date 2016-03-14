#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define VecUI vector<unsigned int>
#define VecB vector<bool>
#define MatUI vector<vector<unsigned int>>

void dfsTopo(const MatUI &graph, vector<unsigned int> &color, const unsigned int &vertice, vector<unsigned int> &order)
{
    color[vertice] = 1;
    
    for(unsigned int i = 0; i < graph[vertice].size(); ++i)
    {
        if(color[graph[vertice][i]] == 0)
            dfsTopo(graph, color, graph[vertice][i], order);
    }

    color[vertice] = 2;
    order.push_back(vertice);
}

void bfs(const MatUI &graph, vector<unsigned int> &color, const unsigned int &vertice)
{
    queue<unsigned int> toVisit;
    toVisit.push(vertice);

    while(!toVisit.empty())
    {
        unsigned int visiting = toVisit.front();
        toVisit.pop();
        color[visiting] = 1;
        for(unsigned int i = 0; i < graph[visiting].size(); ++i)
        {
            if(color[graph[visiting][i]] == 0)
                toVisit.push(graph[visiting][i]);
        }
        color[visiting] = 2;
    }    
}

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int tiles;
    cin >> tiles;
    while(cin >> tiles)
    {
        MatUI adjMat(tiles, VecUI());

	    unsigned int toRead;
        cin >> toRead;
        for(;toRead; --toRead)
        {
            unsigned int u;
            unsigned int v;
            cin >> u;
            cin >> v;
            adjMat[u-1].push_back(v-1);
        }

        // Topologic sort
        vector<unsigned int> order;
        vector<unsigned int> color(tiles, 0);

        for(unsigned int i = 0; i < color.size(); ++i)
        {
            if(color[i] == 0)
                dfsTopo(adjMat, color, i, order);
        }

        fill(color.begin(), color.end(), 0);
        int tries = 0;
        for(int i = order.size() - 1; i >= 0; --i)
        {
            if(color[order[i]] == 0)
            {
               bfs(adjMat, color, order[i]);
                ++tries;
            }
        }
        cout << tries << endl;
    }
    return 0;
} // main()
