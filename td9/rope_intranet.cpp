#include <iostream>
#include <map>
using namespace std;

int main()
{
    int cases;
    cin >> cases;
    cases = 1;
    int wires; 
    while(cin >> wires)
    {
        map<int, int> core;
        int x, y;
        for(unsigned int i = 0; i < wires; ++i)
        {
            cin >> x;
            cin >> y;
            core.emplace(x, y);
        }

        int intersect = 0;
        for(auto it = core.begin(); it != core.end(); ++it)
        {
            auto it2 = it;
            ++it2;
            for(; it2 != core.end(); ++ it2)
            {
                if(it->second > it2->second)
                    ++intersect;
            }
        }
        
        cout << "Case #" << cases++ << ": " << intersect << endl;
    }
    return 0;
}
