#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

bool sortLex(pair<int, int> a, pair<int,int> b)
{
    if(a.first < b.first)
        return true;
    else if(a.first == b.first)
        if(a.second < b.second)
            return true;
    return false;
}

vector<pair<int, int>> criticals;
int cpt = 0;


void Dfs(const vector<vector<unsigned int>> &graph, int startNode, int parent, vector<int> &dfs_num, vector<int> &dfs_low)
{
    dfs_low[startNode] = ++cpt;
    dfs_num[startNode] = cpt;
    
    for(unsigned int i = 0; i < graph[startNode].size(); ++i)
    {
        int nextNode = graph[startNode][i];
        if(parent == nextNode) continue;
        if(dfs_num[nextNode] == -1)
        {
            Dfs(graph, nextNode, startNode, dfs_num, dfs_low);
            dfs_low[startNode] = min(dfs_low[startNode], dfs_low[nextNode]);
            
            if(dfs_low[nextNode] == dfs_num[nextNode])
            {
                if(startNode < nextNode)
                    criticals.push_back(make_pair(startNode, nextNode));
                else
                    criticals.push_back(make_pair(nextNode, startNode));
            }
        }
        else
            dfs_low[startNode] = min(dfs_num[nextNode], dfs_low[startNode]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned int servNb;
    while(cin >> servNb)
    {

	    if(servNb <= 1)
        {
            cout << "O critical links" << endl;
        }
        string con;
        int srv, srvId;
        vector<vector<unsigned int>> graph(servNb, vector<unsigned int>());
        for(unsigned int i = 0; i < servNb; ++i)
        {
            cin >> srvId;
            cin >> con;
            unsigned int nbCon = stoi(string(con.substr(1, con.size() - 2)).c_str());
            for(; nbCon; --nbCon)
            {
                cin >> srv;
                graph[srvId].push_back(srv);
            }
        }

        cpt = 0;        
        criticals.clear();

        vector<int> dfs_num(servNb, -1);
        vector<int> dfs_low(servNb, -1);
        for(unsigned int i = 0; i < servNb; ++i)
        {
            if(dfs_num[i] == -1)
                Dfs(graph, i, -1, dfs_num, dfs_low);
        }

        sort(criticals.begin(), criticals.end(), sortLex);
        cout << criticals.size() << " critical links" << endl;
        for(unsigned int i = 0; i < criticals.size(); ++i)
        {
            cout << criticals[i].first << " - " << criticals[i].second << endl;
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
