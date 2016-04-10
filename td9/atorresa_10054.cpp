#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

unsigned int N;
int graph[50][50];

void dfs(unsigned int start, vector<bool> &visited)
{
	visited[start] = true;
	for(unsigned int i = 0; i < 50; ++i)
	{
		if(graph[start][i] >= 1 && !visited[i])
			dfs(i, visited);
	}
}

void getOrder(unsigned int startNode, vector<unsigned int> &order)
{
	for(unsigned int i = 0; i < 50; ++i)
	{
		if(graph[startNode][i] >= 1)
		{
			--graph[startNode][i];
			--graph[i][startNode];

			getOrder(i, order);

			order.push_back(i + 1);
			order.push_back(startNode + 1);
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    testCases = 1;
    while(cin >> N)
    {
    	if(testCases > 1)
    		cout << endl;

    	memset(graph, 0, sizeof(graph));
    	int deg[50];
    	memset(deg, 0, sizeof(deg));

		for(unsigned int i = 0; i < N; ++i)
    	{
    		unsigned int x, y;
    		cin >> x;
    		cin >> y;
    		++graph[--x][--y];
    		++graph[y][x];
    		++deg[x];
    		++deg[y];
    	}

    	vector<unsigned int> order;
    	vector<bool> visited(50, false);

    	int mindeg = -1;
    	for(unsigned int i = 0; i < 50; ++i)
    	{
    		if(deg[i] > 0)
    		{
    			dfs(i, visited);
    			mindeg = i;
    			break;
    		}
    	}

    	bool unconnected = false;
		for(unsigned int i = 0; i < 50; ++i)
		{
			if(deg[i] > 0 && !visited[i])
				unconnected = true;
			else if(deg[i] % 2 != 0)
				unconnected = true;
		}

		/*for(unsigned int i = 0; i < 50; ++i)
		{
			for(unsigned int j = 0; j < 50; ++j)
				cout << graph[i][j] << " ";
			cout << endl;
		}*/

    	cout << "Case #" << testCases++ << endl;

    	if(unconnected || mindeg == -1)
    	{
    		cout << "some beads may be lost" << endl;
    		continue;
    	}

    	getOrder(mindeg, order);
		for(unsigned int i = 0; i < order.size(); i += 2)
			cout << order[i] << " " << order[i + 1] << endl;
    }
    return 0;
} // main()
