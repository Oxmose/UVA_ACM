#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <climits>

#define MatI vector<vector<int>>
#define VecI vector<int>
#define VecB vector<bool>

int graph[100][100];

using namespace std;

void BF(const unsigned int &startNode, VecI &dists)
{
	// Init
	dists[startNode] = 0;
	unsigned int nodesCount = dists.size();

	for(unsigned int j = 0; j < nodesCount; ++j)
	    cout << dists[j] << " M " << nodesCount << endl;

	// BF
	for(unsigned int m = 1; m < nodesCount; ++m)
	{
		for(unsigned int i = 0; i < nodesCount; ++i)
		{
			for(unsigned int j = 0; j < nodesCount; ++j)
			{
				if(graph[i][j] == 1)
				{
					if(dists[j] > dists[i] + 1)
					{
						dists[j] = dists[i] + 1;
					}
				}
			}
		}
	}

	cout << endl;
	for(unsigned int j = 0; j < nodesCount; ++j)
		    cout << dists[j] << " M " << nodesCount << endl;
	cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(3);

    unsigned int fst;
    unsigned int snd;
    unsigned int caseC = 0;
    while(cin >> fst)
    {
    	caseC++;
    	cin >> snd;
    	if(fst == snd && snd == 0)
    		break;
    	memset(graph, 0, sizeof(graph));
    	map<int, int> corresp;

    	unsigned int max = 0;

    	while(fst != 0 && snd != 0)
    	{
    		if(corresp.find(fst) == corresp.end())
    		{
    			corresp.emplace(fst, max++);
    		}
    		if(corresp.find(snd) == corresp.end())
			{
				corresp.emplace(snd, max++);
			}

    		graph[corresp[fst]][corresp[snd]] = 1;

    		cin >> fst;
    		cin >> snd;
    	}

    	unsigned int count = 0;
    	unsigned int value = 0;
    	for(unsigned int i = 0; i < max; ++i)
    	{
    		VecI dists(max, INT_MAX);
    		BF(i, dists);
    		/*for(unsigned int j = 0; j < max; ++j)
    			cout << dists[j] << " M " << max << " I" << i << endl;*/
    		cout << endl;
    		for(unsigned int j = 0; j < max; ++j)
    		{
    			if(j == i)
    				continue;

    			++count;
    			value += dists[j];
    		}
    	}

    	cout << "Case " << caseC << ": average length between pages = " << (double) value / (double) count << " clicks" << endl;
    }
    return 0;
} // main()
