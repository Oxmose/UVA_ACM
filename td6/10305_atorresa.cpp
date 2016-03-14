#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<unsigned int>> MatUInt;

void dfsTopo(const MatUInt &graph, vector<unsigned int> &color, const unsigned int &vertice, vector<unsigned int> &order)
{
    color[vertice] = 1;
    
    for(unsigned int i = 0; i < graph[vertice].size(); ++i)
    {
        if(color[graph[vertice][i]] == 0)
            dfsTopo(graph, color, graph[vertice][i], order);
    }

    color[vertice] = 2;
    order.push_back(vertice);
}

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int tasksCount;

    while(cin >> tasksCount)
    {
        
        unsigned int precedences;
        cin >> precedences;

        if(precedences == 0 && tasksCount == precedences)
            return 0;

        MatUInt adjList(tasksCount, vector<unsigned int>());
        for(unsigned int i = 0; i < tasksCount; ++i)
        {
            adjList[i].push_back(i);
        }

        while(precedences)
        {
            unsigned int buff;
            cin >> buff;
            unsigned int index = buff - 1;
            cin >> buff;
            adjList[index].push_back(buff - 1);
            --precedences;
        }

        vector<unsigned int> order;
        vector<unsigned int> color(tasksCount, 0);

        for(unsigned int i = 0; i < color.size(); ++i)
        {
            if(color[i] == 0)
                dfsTopo(adjList, color, i, order);
        }

        for(int i = order.size() - 1; i >= 0; --i)
        {
            if(i == 0)
                cout << order[i] + 1;
            else
                cout << order[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
} // main()
