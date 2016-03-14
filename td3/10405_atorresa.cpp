#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    string firstSeq;
    string secondSeq;

    while(getline(cin, firstSeq))
    {
        getline(cin, secondSeq);

        // Init matrix
        // We init on 0 for the first column and line (save time)
        // Actually, comparisions will take place at [1,1]
        // Avoid to to two loops on first line and column to init values with conditions
        unsigned int opt[firstSeq.size() + 1][secondSeq.size() + 1];
        for(unsigned int i = 0; i < firstSeq.size() + 1; ++i)
            for(unsigned int j = 0; j < secondSeq.size() + 1; ++j)
                opt[i][j] = 0;

        // Dyn (if we are equal we add 1 to the optimal (foud at top left)
        // else just take the max of the last optimals
        // on top of left
        for(unsigned int i = 1; i < firstSeq.size() + 1; ++i)
        {
            for(unsigned int j = 1; j < secondSeq.size() + 1; ++j)
            {
                if(firstSeq[i - 1] == secondSeq[j - 1])
                    opt[i][j] = opt[i - 1][j - 1] + 1;
                else if(opt[i - 1][j] >= opt[i][j - 1])
                    opt[i][j] = opt[i - 1][j];
                else 
                    opt[i][j] = opt[i][j - 1];
            }
        }           

        cout << opt[firstSeq.size()][secondSeq.size()] << endl;
    }
    return 0;
} // main()
