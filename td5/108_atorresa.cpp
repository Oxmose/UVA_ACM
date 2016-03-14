#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int size;
    while(cin >> size)
    {
        int array[size][size];
        int sums[size][size + 1];
        unsigned int i = 0;
        unsigned int j = 0;
        int cpt = size * size;

        // Get data
        while(cpt)
        {
            cin >> array[i][j];
            ++j;
            if(j == size)
            {
                ++i;
                j = 0;
            }
            --cpt;
        }

        // We compute the sum for each rows by lines
        int sum;
        memset(sums, 0, sizeof(sums));
        for(unsigned int i = 0; i < size; ++i)
        {
            sum = 0;
            for(unsigned int j = 0; j < size; ++j)
            {
                sum += array[i][j];
                sums[i][j + 1] = sum;
            }
        }

        /*for(unsigned int i = 0; i < size; ++i)
        {
            for(unsigned int j = 0; j <= size; ++j)
                cout << setw(5) << sums[i][j] << " ";

            cout << endl;
        }*/

        int maxSum = 0;
        
        //for(unsigned int h = 0; h < size; ++h)
        //{
            // For each columns at the begining
            for(unsigned int w = 1; w <= size; ++w)
            {
                // Next(s) rows
                for(unsigned int j = w; j <= size; ++j)
                { 
                    int partSum = 0; 
                    // For each lines              
                    for(unsigned int i = 0; i < size; ++i)
                    {
                        // We dont want any negative output
                        if(partSum < 0)
                            partSum= 0;
                        //cout << sums[i][w] << " ";
                        // Sum of the sums (same process than last practical)
                        partSum += sums[i][j] - sums[i][w - 1];

                        if(maxSum < partSum)
                            maxSum = partSum;
                    }
                    //cout << endl;
                    
                }
                
            }
        //}
        cout << maxSum << endl;
    }

    return 0;
} // main()
