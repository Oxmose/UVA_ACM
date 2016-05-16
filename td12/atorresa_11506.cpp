#include <iostream>
#include <vector>
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
    int m, w;
    //map<unsigned int, unsigned int> machineCost;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin >> m)
    {       
        cin >> w;
        if(m == w && w == 0) return 0;

        vector<vector<int>> graph(2 * m, vector<int>(2 * m, -1));
        int id1, id2, val;
        for(unsigned int i = 0; i < m - 2; ++i)
        {
            cin >> id1 >> val;
            --id1;
            //machineCost[id-1] = val;
            graph[id1][m + id1]=val;
            graph[m + id1][id1]=val;
        }
        for(unsigned int i = 0; i < w; ++i)
        {
            cin >> id1 >> id2 >> val;
            --id1;
            --id2;
            
            // if boss machine
            if(id1 == 0 || id2 == 0)
            {
                int client;
                if(id1 != 0)
                    client = id1;
                else
                    client = id2;

                id1 = 0;

                graph[id1][client] = val;
                if(client == m - 1)
                {                    
                    graph[client][id1] = val;
                }
                else
                {
                    graph[m + client][id1] = val;
                }
            }
            else if(id1 == m - 1 || id2 == m - 1)
            {
                int client;
                if(id1 != m - 1)
                    client = id1;
                else
                    client = id2;

                id1 = m - 1;

		        graph[id1][client] = val;
                graph[client + m][id1] = val;                
            }
            else
            {
                graph[id1 + m][id2] = val;
                graph[id2 + m][id1] = val;
            }	
        }

        
        cout << FF(graph, 0, m - 1) << endl;
    }
    return 0;
}
