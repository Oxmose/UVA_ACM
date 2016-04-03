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

void Dfs(const vector<vector<unsigned int>> &graph, const unsigned int &startNode, const unsigned &parent, unsigned int cpt, vector<int> &dfs_num, vector<int> &dfs_low)
{
    dfs_low[startNode] = ++cpt;
    dfs_num[startNode] = cpt;
    
    for(unsigned int i = 0; i < graph[startNode].size(); ++i)
    {
        if(dfs_num[graph[startNode][i]] == -1)
        {
            Dfs(graph, graph[startNode][i], startNode, cpt, dfs_num, dfs_low);
            dfs_low[startNode] = min(dfs_low[startNode], dfs_low[graph[startNode][i]]);
            if(dfs_low[graph[startNode][i]] == dfs_num[graph[startNode][i]])
            {
                if(startNode < graph[startNode][i])
                    criticals.push_back(make_pair(startNode, graph[startNode][i]));
                else
                    criticals.push_back(make_pair(graph[startNode][i], startNode));
            }
        }
        else if(graph[startNode][i] != parent)
            dfs_low[startNode] = min(dfs_num[graph[startNode][i]], dfs_low[startNode]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    bool fst = true;
    unsigned int servNb;
    while(cin >> servNb)
    {
        if(!fst)
            cout << endl;
        else
            fst = false;

	    if(servNb <= 1)
        {
            cout << "O critical links" << endl;
        }
        string con;
        int srv;
        vector<vector<unsigned int>> graph(servNb, vector<unsigned int>());
        for(unsigned int i = 0; i < servNb; ++i)
        {
            cin >> srv;
            cin >> con;
            unsigned int nbCon = stoi(string(con.substr(1, con.size() - 2)).c_str());
            for(; nbCon; --nbCon)
            {
                cin >> srv;
                graph[i].push_back(srv);
            }
        }
        vector<int> dfs_low(servNb, -1);
        vector<int> dfs_num(servNb, -1);

        for(unsigned int i = 0; i < dfs_num.size(); ++i)
        {
            if(dfs_num[i] == -1)
                Dfs(graph, i, i, 0, dfs_num, dfs_low);
        }
        sort(criticals.begin(), criticals.end(), sortLex);
        cout << criticals.size() << " critical links" << endl;
        for(unsigned int i = 0; i < criticals.size(); ++i)
        {
            cout << criticals[i].first << " - " << criticals[i].second << endl;
        }

        criticals.clear();
        /*for(unsigned int i = 0; i < graph.size(); ++i)
        {
            for(unsigned int j = 0; j < graph[i].size(); ++j)
                cout << graph[i][j] << " ";
            cout << endl;
        }*/
    }

    return 0;
}
