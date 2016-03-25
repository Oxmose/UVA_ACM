#include <iostream>
#include <vector>
#include <utility>
#include <climits>

#define VecIP vector<vector<pair<int, int>>>
#define VecI vector<int>
#define VecB vector<bool>

using namespace std;

bool BF(const VecIP &graph, VecI &costs)
{
	// Init
	unsigned int visitCount = graph.size();
	costs[0] = 0;


	for(unsigned int m = 1; m < visitCount; ++m)
	{
		for(unsigned int i = 0; i < visitCount; ++i)
		{
			for(unsigned int j = 0; j < graph[i].size(); ++j)
			{
				if(costs[graph[i][j].first] > 0 && costs[graph[i][j].first] > costs[i] + graph[i][j].second)
					costs[graph[i][j].first] = costs[i] + graph[i][j].second;
			}
		}
	}

	for(unsigned int i = 0; i < visitCount; ++i)
	{
		for(unsigned int j = 0; j < graph[i].size(); ++j)
		{
			if(costs[graph[i][j].first] > costs[i] + graph[i][j].second)
				return false;
		}
	}
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
				graph[i][j].second = -energies[graph[i][j].first];
			}
		}
		VecI costs(roomsCount, INT_MAX);

		BF(graph, costs);

		if(costs[roomsCount - 1] < -100)
			cout << "winnable" << endl;
		else
			cout << "hopeless" << endl;


    }
    return 0;
} // main()
