#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define VecUI vector<unsigned int>
#define VecB vector<bool>
#define MatUI vector<vector<unsigned int>>

bool isBipart(const MatUI &graph, VecB &visited, VecUI &set, const unsigned int &vertex, const unsigned int &setVal)
{
    if(setVal == 1)
        set[vertex] = 2;
    else
        set[vertex] = 1;

    visited[vertex] = true;

    for(unsigned int i = 0; i < graph[vertex].size(); ++i)
        if(set[graph[vertex][i]] == set[vertex])
            return false;

    for(unsigned int i = 0; i < graph[vertex].size(); ++i)
        if(! visited[graph[vertex][i]])
            if(! isBipart(graph, visited, set, graph[vertex][i], set[vertex]))
                return false;

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int verticesCount;
    while(cin >> verticesCount)
    {
        if(verticesCount == 0)
            return 0;

        unsigned int x;
        unsigned int y;
        MatUI graph(verticesCount, vector<unsigned int>());
        VecUI set(verticesCount, 0);
        VecB visited(verticesCount, false);
        while(true)
        {
            cin >> x;
            cin >> y;
            if(x == y && x == 0)
                break;

            --x;
            --y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        if(isBipart(graph, visited, set, 0, 1))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
} // main()
