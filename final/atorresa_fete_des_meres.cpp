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
    int cases;
    cin >> cases;
    while(cases--)
    {
        int nbCadCli;
        cin >> nbCadCli;
        vector<vector<int>> graph(nbCadCli * 2 + 2, vector<int>(nbCadCli * 2 + 2, 0));

        for(int i = 0; i < nbCadCli; ++i)
        {
            for(int j = 0; j < nbCadCli; ++j)
            {
                int val;
                cin >> val;
                if(val)
                {
                    graph[i][nbCadCli + j] = 1;
                }
            }
        }
        for(int i = 0; i < nbCadCli; ++i)
        {
            graph[nbCadCli * 2][i] = 1;
            graph[i + nbCadCli][nbCadCli * 2 + 1] = 1;
        }
        /*for(int i = 0; i < nbCadCli * 2; ++i)
        {
            for(int j = 0; j < nbCadCli * 2; ++j)
            {
                cout <<  graph[i][j];                
            }
            cout << endl;
        }*/
        if(nbCadCli <= FF(graph, nbCadCli * 2, nbCadCli * 2 + 1))
            cout << "Yes we can" << endl;
        else
            cout << "Pas possible" << endl;
    }

    return 0;
}
