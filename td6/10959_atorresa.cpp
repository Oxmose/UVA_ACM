#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

unsigned int p = 0;

unsigned int gnum[1000];
unsigned int graph[1000][1000];
int visited[1000];

queue<int> nextE;

void bfs()
{
    while(!nextE.empty())
    {
        unsigned int from = nextE.front();
        nextE.pop();
        for(unsigned int i = 1; i < p; ++i)
        {
            if(graph[from][i] && !visited[i])
            {
                visited[i] = true;
                gnum[i] = gnum[from] + 1;
                nextE.push(i);
            }
        }
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    unsigned int n;

    cin >> n;
    while(n > 0)
    {
        cin.ignore();
        unsigned int d;
            
        cin >> p;
        cin >> d;

        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));

        // Creating adjacence matrix
        for(unsigned int i = 0; i < d; ++i)
        {
            int p1;
            int p2;
            cin >> p1 >> p2;
            graph[p1][p2] = 1;
            graph[p2][p1] = 1; 
        }

        nextE.push(0);
        gnum[0] = 0;
        bfs();

        for(unsigned int i = 1; i < p; ++i)
            cout << gnum[i] << endl;

	    if(n != 1)
            cout << endl;
        --n;
    }
    return 0;
}
