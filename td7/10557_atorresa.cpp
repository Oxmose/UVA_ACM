#include <iostream>
#include <vector>
#include <utility>
#include <climits>

#define VecIP vector<vector<pair<int, int>>>
#define VecI vector<int>
#define VecB vector<bool>

using namespace std;

bool dfs(const VecIP &graph, VecB &visited, const unsigned int &toVisit)
{
	if(toVisit == graph.size() - 1) return true;

	visited[toVisit] = true;

	for(unsigned int i = 0; i < graph[toVisit].size(); ++i)
	{
		if(!visited[graph[toVisit][i].first])
			if(dfs(graph, visited, graph[toVisit][i].first))
				return true;
	}
	return false;
}

bool BF(const VecIP &graph, VecI &costs)
{
	// Init
	unsigned int visitCount = graph.size();
	costs[0] = 100;
	vector<bool> visited(visitCount, false);

	// Relaxes the edges
	for(unsigned int m = 1; m < visitCount; ++m)
		for(unsigned int i = 0; i < visitCount; ++i)
			for(unsigned int j = 0; j < graph[i].size(); ++j)
				if(costs[i] > 0 && costs[graph[i][j].first] < costs[i] + graph[i][j].second)
					costs[graph[i][j].first] = costs[i] + graph[i][j].second;

    // Check for cycle
	for(unsigned int i = 0; i < visitCount; ++i)
		for(unsigned int j = 0; j < graph[i].size(); ++j)
			if(costs[i] > 0 && costs[graph[i][j].first] < costs[i] + graph[i][j].second && !visited[i])
				return false;

	return true;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int roomsCount;
    while(cin >> roomsCount)
    {
    	if(roomsCount == -1)
    		break;

    	VecIP graph(roomsCount, vector<pair<int, int>>());
    	VecI energies(roomsCount);

        // Get data
    	unsigned int doors;
    	for(int i = 0; i < roomsCount; ++i)
    	{
    		cin >> energies[i];
    		cin >> doors;
    		for(unsigned int j = 0; j < doors; ++j)
    		{
    			int room;
    			cin >> room;
    			graph[i].push_back(make_pair(--room, 0));
    		}
    	}
		for(int i = 0; i < roomsCount; ++i)
		{
			for(unsigned int j = 0; j < graph[i].size(); ++j)
			{
				graph[i][j].second = energies[graph[i][j].first];
			}
		}

		VecI costs(roomsCount, INT_MIN + 100001);
        bool winnable = false;
        // If there is an energy generator cycle
		if(!BF(graph, costs))
		{
            // If we can access the end node then it is winnable
            // Since we can just "pump" in the cycle
			VecB visited(roomsCount, false);
			if(dfs(graph, visited, 0))
				winnable = true;
		}
        // If no cycle and we can access the end node wi our energy
		if (winnable || costs[roomsCount - 1] > 0)
			cout << "winnable" << endl;
		else
			cout << "hopeless" << endl;

    }
    return 0;
} // main()
