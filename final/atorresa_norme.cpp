#include <iostream>
#include <vector>
#include <map>
#include <climits>
#include <cstring>
using namespace std;

/*
*
*	NE FONCTIONNE PAS!!!
*       La contruction de l'arbre n'est pas bonne
*
*/

struct vertex
{
    int id;
    vector<struct vertex*> childs;
};
typedef struct vertex vertex;

void dfs(vertex *node, int t)
{
    if(node->id == -1)
    {
        for(unsigned int i = 0; i < node->childs.size(); ++i)
            dfs(node->childs[i], t);
    }
    else
    {
        for(unsigned int i = 0; i < t; ++i)
            cout << "\t";
        cout << node->id << endl;
        for(unsigned int i = 0; i < node->childs.size(); ++i)
            dfs(node->childs[i], t + 1);
    }
}

int minCover(vertex *node)
{
    if(node->id == -1)
    {
        int max = 0;
        for(unsigned int i = 0; i < node->childs.size(); ++i)
            max += minCover(node->childs[i]);
        return max;
    }

    if(!node || node->childs.empty())
        return 0;
        
    int min = 1;

    // Try to cover the current node
    for(unsigned int i = 0; i < node->childs.size(); ++i)
    {
        min += minCover(node->childs[i]);
    }

    // Try not to cover
    int newMin = 0;
    for(unsigned int i = 0; i < node->childs.size(); ++i)
    {
        newMin += 1;
        for(unsigned int j = 0; j < node->childs[i]->childs.size(); ++j)
        {
            newMin += minCover(node->childs[i]->childs[j]);
        }
    }

    //cout << min << " MIN " << newMin << " newMin" << endl;

    if(newMin != 0 && newMin < min)
        return newMin;
    else 
        return min;
}

int main()
{
    int rooms;
    while(cin >> rooms)
    {
        if(rooms == 0)
            break;

        vertex *graph = new vertex;
        graph->id = -1;
        map<int, vertex*> roomIdCor;
        map<int, bool> rooted;

        roomIdCor[-1] = graph;

        for(int i = 0; i < rooms; ++i)
        {
            vertex *current;
            if(roomIdCor.find(i) != roomIdCor.end())
            {
                current = roomIdCor[i];
            }
            else
            {
                current = new vertex;
                roomIdCor[i] = current;
                current->id = i;                
            }

            int count, adj;
            cin >> count;
            while(count)
            {
                cin >> adj;
                --adj;
                if(rooted.find(adj) != rooted.end())
                {
                    roomIdCor[adj]->childs.push_back(current);
                    rooted[i] = true;
                }
                else if(adj > i)
                {
                    vertex *child = new vertex;
                    child->id = adj,
                    roomIdCor[adj] = child;
                    rooted[adj] = true;
                    current->childs.push_back(child);
                }
                
                --count;
            }
        }
        for(unsigned int i = 0; i < rooms; ++i)
        {
            if(rooted.find(i) == rooted.end())
            {
                graph->childs.push_back(roomIdCor[i]);
            }
        }
        /*int size = graph.size();
        for(unsigned int i = 0; i < graph.size() - 2; ++i)
        {
            graph[i][size - 2] = 1;
            graph[size - 2][i] = 1;
            graph[size - 1][i] = 1;
            graph[i][size - 1] = 1;
        }*/

        dfs(graph, 0);
        cout << minCover(graph) << endl;
        cout << endl << endl;
    }
    return 0;
}
