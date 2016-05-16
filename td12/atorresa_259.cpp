#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstring>
#include <vector>
#include <climits>
#include <queue>
#include <iomanip>

using namespace std;

map<unsigned int, unsigned int> jobs;

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

int FF(vector<vector<int>> graph, int source, int target)
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
    //cout << "MAXFLOX : " << flow << endl;
    bool found = false;
    string sol("");
    for(unsigned int i = 0; i < 10; ++i)
    {
        found = false;
        for(unsigned int j = 11; j < 37; ++j)
        {
            if(residual[j][i] == 0 && jobs.find(j) != jobs.end())
            {
                sol += (char) (j - 11 + 'A');
                found = true;
                break;
            }
        }
        if(!found)
            sol += "_";
    }
    
    /*for(unsigned int i = 0; i < 38; ++i)
    {
        
        for(unsigned int j = 0; j < 38; ++j)
        {
            cout << residual[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    /*for(unsigned int i = 0; i < 38; ++i)
    {
        cout << "i: " << setw(3) << left << i << "| ";
        for(unsigned int j = 0; j < 38; ++j)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }*/

    for(unsigned int i = 11; i < 37; ++i)
    {
        if(residual[37][i] > 0)
        {
            //cout << sol << endl;
            //cout << "STILL " << (char) (i - 11 + 'A') << endl;
            cout << "!" << endl;
            return flow;
        }
    }
    cout << sol << endl;
    return flow;
}

int main()
{
    vector<vector<int>> graph(38, vector<int>(38, -1));

   
    string line;
    while(getline(cin, line))
    {
        if(line.size() == 0)
        {
            // Add source and targer
            for(unsigned int i = 11; i < 37; ++i)
            {
                if(jobs.find(i) != jobs.end())
                    graph[37][i] = jobs[i];
            }
            for(unsigned int i = 0; i < 10; ++i)
            {
                graph[i][10] = 1;
            }

            

	        FF(graph, 37, 10);

            graph = vector<vector<int>>(38, vector<int>(38, -1));
            jobs.clear();
        }
        else
        {
            stringstream ss(line);
            string buff("");
            ss >> buff;

            unsigned int job = buff[0] - 'A' + 11;
            jobs[job] = buff[1] - '0';
            buff = "";

            ss >> buff;
            for(char i : buff)
            {
                if(i == ';')
                    break;

                graph[job][i - '0'] = 1;
                graph[i - '0'][job] = 0;
            }
        }
    }

    // Add source and targer
    for(unsigned int i = 11; i < 37; ++i)
    {
        if(jobs.find(i) != jobs.end())
            graph[37][i] = jobs[i];
    }
    for(unsigned int i = 0; i < 10; ++i)
    {
        graph[i][10] = 1;
    }    

    FF(graph, 37, 10);
    return 0;
}
