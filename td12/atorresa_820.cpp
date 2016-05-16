#include <iostream>
#include <cstring>
#include <queue>
#include <climits>

using namespace std;

bool Bfs(vector<vector<int>> &graph, int source, int target, vector<int> &parent)
{
    size_t vectSize = graph.size();
    bool visited[vectSize];
    memset(visited, 0, sizeof(visited));

    queue<int> toVisit;
    toVisit.push(source);

    parent[source] = -1;
    visited[source] = true;

    while(!toVisit.empty())
    {
        int node = toVisit.front();
        toVisit.pop();

        for(unsigned int i = 0; i < vectSize; ++i)
        {
            if(graph[node][i] > 0 && !visited[i])
            {
                visited[i] = true;
                toVisit.push(i);
                parent[i] = node;
            }
        }
    }
    return visited[target];
}

int FF(vector<vector<int>> &graph, int source, int target)
{
    size_t vectSize = graph.size();
    unsigned int flow = 0;
    vector<vector<int>> residual(vectSize, vector<int>(vectSize));

    for(unsigned int i = 0; i < vectSize; ++i)
        for(unsigned int j = 0; j < vectSize; ++j)
            residual[i][j] = graph[i][j];

    vector<int> parent(vectSize);

    while(Bfs(residual, source, target, parent))
    {
        unsigned int j;
        unsigned int tmpFlow = INT_MAX;
        for(unsigned int i = target; i != source; i = parent[i])
        {
            j = parent[i];
            if(tmpFlow > residual[j][i])
                tmpFlow = residual[j][i];
        }

        for(unsigned int i = target; i != source; i = parent[i])
        {
            j = parent[i];
            residual[j][i] -= tmpFlow;
            residual[i][j] += tmpFlow;
        }
        
        flow += tmpFlow;
    }
    return flow;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int count = 1;
    int nodes;

    while(cin >> nodes)
    {
        if(nodes == 0) break;

        vector<vector<int>> graph(nodes, vector<int>(nodes));
        
        int source, target, links;
        cin >> source >> target >> links;
        --source;
        --target;

        while(links)
        {
            int from, to, cap;
            cin >> from >> to >> cap;
            graph[from - 1][to - 1] += cap;
            graph[to - 1][from -1] += cap;
            --links;
        }
        int bandwidth = FF(graph, source, target);        

        cout << "Network " << count++ << endl;
        cout << "The bandwidth is " << bandwidth << "." << endl << endl;
    }

    return 0;
}
