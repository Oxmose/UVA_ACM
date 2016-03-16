#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

#define MatD vector<vector<double>>
#define VecB vector<bool>
#define VecD vector<double>


// Get the node with the minimum weight that has not been already visited
int getMinWeight(const VecD &vertexWeight, const VecB &visited)
{
    double min = 0;
    unsigned int vertice = -1;
    bool assigned = false;
    for(unsigned int i = 0; i < vertexWeight.size(); ++i)
    {
	    // If we never assigned weight to the node
        if(!visited[i] && !assigned && vertexWeight[i] > -1)
        {
            assigned = true;
            min = vertexWeight[i];
            vertice = i;
        }
        else if(!visited[i] && vertexWeight[i] > -1 && vertexWeight[i] < min)
        {
            min = vertexWeight[i];
            vertice = i;
        }
    }
    return vertice;
}

void bfsWeight(const MatD &graph, VecD &vertexWeight, VecB &visited, unsigned int &toVisitCount)
{
    while(toVisitCount)
    {
        unsigned int toVisit = getMinWeight(vertexWeight, visited);
        visited[toVisit] = true;
        --toVisitCount;

	    // Browse th graph and adding the weight to the nodes if it is better
        for(unsigned int i = 0; i < graph[toVisit].size(); ++i)
        {
            if(i != toVisit && !visited[i] && (vertexWeight[i] == -1 || vertexWeight[i] > graph[toVisit][i]))
                vertexWeight[i] = graph[toVisit][i];
        }        
    }
} 

int main()
{
    ios_base::sync_with_stdio(false);
    cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    cout.precision(2);

    unsigned int cases;
    cin >> cases;
    unsigned int satChans;
    while(cin >> satChans)
    {
        unsigned int outPosts;
        cin >> outPosts;
        vector<pair<int, int>> outPostsCoor(outPosts);
        MatD graph(outPosts, VecD(outPosts));
        
        for(unsigned int i = 0; i < outPosts; ++i)
        {
            int x;
            int y;
            cin >> x;
            cin >> y;
            outPostsCoor[i] = make_pair(x, y);

            graph[i][i] = -1;

            for(unsigned int j = 0; j < i; ++j)
            {
                double fst = outPostsCoor[i].first - outPostsCoor[j].first;
                double snd = outPostsCoor[i].second - outPostsCoor[j].second;
                double distance = sqrt(fst * fst + snd * snd);
                graph[i][j] = distance;
                graph[j][i] = distance;
            }
        }
        
        unsigned int toVisitCount = outPosts;
        VecD vertexWeight(outPosts, -1);
        VecB visited(outPosts, false);
        vertexWeight[0] = 0;
    
        // We get the minimum covering tree
        bfsWeight(graph, vertexWeight, visited, toVisitCount);

        sort(vertexWeight.begin(), vertexWeight.end());

        cout << vertexWeight[outPosts - satChans] << endl;
        
    }
    return 0;
} // main()
