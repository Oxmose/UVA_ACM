#include <iostream>

using namespace std;

int main()
{
    // Don't sync C++ and C I/O (OPTI)
    ios_base::sync_with_stdio(false);
    unsigned int vesselsCount;
    while (cin >> vesselsCount)
    {
        unsigned int containersCount;
        cin >> containersCount;

        cin.ignore();

        // Create array containning capacity ofthe vessels and containers count
        unsigned int vesselsCapacity[vesselsCount];
        unsigned int containers[containersCount];


        // Get the maximum capacity a vessel can have
        unsigned int maxCapacity = 0;
        for(unsigned int i = 0; i < vesselsCount; ++i)
        {
            cin >> vesselsCapacity[i];
            if(maxCapacity < vesselsCapacity[i])
                maxCapacity = vesselsCapacity[i];
        }

        // 
        unsigned int toFill = 0;
        unsigned int toPut = vesselsCount;

        // Compute the total capacity of milk
        unsigned int total = 0;
        for(unsigned int i = 0; i < vesselsCount; ++i)
            total += vesselsCapacity[i];

        // If we only have one container then we need to get one
        // capable of containing the total cpacity of milk
        if(containersCount == 1)
        {
            cout << total << endl;
            continue;
        }

        // If there are more containers than vessels, let just select
        // container that have no more than the max capacity of a vessel
        if(containersCount >= vesselsCount)
        {
            cout << maxCapacity << endl;
            continue;
        }

        unsigned int sup = total;
        unsigned int inf = maxCapacity;

        // Apply dichotomy on the containers size
        unsigned lastMax = (maxCapacity + total) / 2;
        while(true)
        {
            toPut = vesselsCount;
            toFill = 0;
            // Init the content of containers to 0;
            for(unsigned int i = 0; i < containersCount; ++i)
                containers[i] = 0;

            // For eahc vessels, let's put theuir content in the containers
            for(unsigned int i = 0; i < vesselsCount; ++i)
            {
                // If we reached the containers count
                if(toFill > containersCount - 1) break;

                // If we reached the maximum capacity of the current containers (and there are 
                // empty containers left)
                if(containers[toFill] + vesselsCapacity[i] > lastMax)
                {
                    ++toFill;
                    if(toFill > containersCount - 1) break;
                    containers[toFill] += vesselsCapacity[i];
                    --toPut;
                }
                else
                {
                    --toPut;
                    containers[toFill] += vesselsCapacity[i];
                }
            }

            // if we emptied all the vessels
            unsigned int newMax;
            if(toPut == 0)
            {
                maxCapacity = lastMax;
                newMax = (inf + lastMax) / 2;
                sup = lastMax;
            }
            // if not
            else
            {
                newMax = (lastMax + sup) / 2;
                inf = lastMax;
            }

            // If we reached the perfect capacity for the containers
            if(lastMax == newMax)
                break;

            lastMax = newMax;
        }
        cout << maxCapacity << endl;
    }
    return 0;
} // main()
