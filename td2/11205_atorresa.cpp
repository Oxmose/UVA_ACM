#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// OPTI GLOBAL VARS
unsigned symsCount;
unsigned int ledsCount;

inline unsigned int evalEquality(const string *reps, const vector<unsigned int> &maskIndex)
{
    unsigned int max = maskIndex.size();
    int maxVal = 0;

    for(unsigned int i : maskIndex)
    {
        if(i > maxVal)
            maxVal = i;
    }

    for(unsigned int l = maxVal; l < ledsCount; ++l)
    {
        if(find(maskIndex.begin(), maskIndex.end(), l) != maskIndex.end()) continue;

        // Test for equality, each composition must be at least
        // at distance 1 from each others compositions
        bool hasEq = false;

        for(unsigned int i = 0; i < symsCount - 1 && !hasEq; ++i)
        {
            string val = reps[i];
            // Compute the value of the current representation
            val.erase(l, 1);
            for(int j = maskIndex.size() - 1; j >= 0; --j)
                val = val.erase(maskIndex[j], 1);

            // Compare to others
            for(unsigned int j = i + 1; j < symsCount; ++j)
            {
                string val2 = reps[j];

                // Compute the value of the current representation
                val2.erase(l, 1);
                for(int k = maskIndex.size() - 1; k >= 0; --k)
                    val2 = val2.erase(maskIndex[k], 1);

                if(val.compare(val2) == 0)
                {
                    hasEq = true;
                    break;
                }
            }
        }

        if(hasEq) continue;

        vector<unsigned int> newMasks = maskIndex;
        newMasks.push_back(l);
        unsigned int newMax = evalEquality(reps, newMasks);
        if(newMax > max)
            max = newMax;
    }

    return max;
} // evalEquality(const string*, const vector<unsigned int>&)

int main()
{
    // OPTI
    ios_base::sync_with_stdio(false);

    // Read the input
    unsigned int instances;
    cin >> instances;
    cin.ignore();

    while(cin >> ledsCount && instances > 0)
    {
        cin.ignore();
        cin >> symsCount;
        cin.ignore();
        string reps[symsCount];


        for(unsigned int i = 0; i < symsCount; ++i)
        {
            string val;
            for(unsigned int j = 0; j < ledsCount; ++j)
            {
                cin >> val;
                reps[i] += val;
            }
            cin.ignore();
        }

        // If there are exactly the number of leds to display the symbols
        if(log2(symsCount) == ledsCount)
        {
            cout << ledsCount << endl;
            --instances;
            continue;
        }

        // Compute which leds are deletable
        vector<unsigned int> initV;
        unsigned int maxDeletalble = evalEquality(reps, initV);
        cout << ledsCount - maxDeletalble << endl;
        --instances;
    }

    return 0;
} // main()
