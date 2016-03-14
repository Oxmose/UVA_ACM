#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //  Don't sync C++ and C I/O (OPTI)
    ios_base::sync_with_stdio(false);

    int value;
    vector<int> positions;
    unsigned int testNb = 1;

    bool quit = false;

    while(cin >> value)
    {
        // If end of the sequence
        if(value == -1)
        {
            if (quit == true)
                return 0;
            quit = true;

            if(positions.size() == 0) continue;

            vector<int> longestIncreasingSeq(positions.size());
            int max = 0;

            // Using int instead of unsigned int because i can be < 0
            for(int i = positions.size() - 1; i >= 0; --i) 
            {
                longestIncreasingSeq[i] = 1;
                for(int j = positions.size() - 1; j > i; --j)
                {
                    // if we can still select position j and the number of intercepted positions from j is 
                    // higher (or equal) than the  number of intercepted positions from here (i) then select
                    // i and all it's intercepted positions
                    if(positions[i] >= positions[j] && longestIncreasingSeq[i] <= longestIncreasingSeq[j])
                    {
                        longestIncreasingSeq[i] = longestIncreasingSeq[j]+1;
                    }
                }
                // Increase the max if we found a better solution
                if(longestIncreasingSeq[i] > max) 
                    max = longestIncreasingSeq[i];
            }
            if(testNb != 1)
                cout << endl;
            cout << "Test #" << testNb++  << ":" << endl << "  maximum possible interceptions: " << max << endl;
            positions.clear();
        }
        else
        {
            quit = false;
            positions.push_back(value);
        }
    }
    return 0;
} // main()
