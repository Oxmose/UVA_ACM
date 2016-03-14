#include <iostream>

using namespace std;

/*
**
** a penny : 1cts
** a nickel : 5cts
** a dime : 10cts
** a quarter : 25cts
** a half-dollar : 50cts
**
*/

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int change[5];
    change[0] = 1;
    change[1] = 5;
    change[2] = 10;
    change[3] = 25;
    change[4] = 50;

    unsigned int changeAmount;
    while(cin >> changeAmount)
    {

        
        if(changeAmount < 5)
        {
            cout << "There is only 1 way to produce " << changeAmount << " cents change." << endl;
            continue;
        }

	    long long posibilities[changeAmount + 1];        
		for(unsigned int i = 0; i < changeAmount + 1; ++i)
			posibilities[i] = change[0];

		for(unsigned int i = 1; i < 5; ++i)
		{
			for(unsigned int j = change[i]; j < changeAmount + 1; ++j)
				posibilities[j] += posibilities[j - change[i]];
        }

        cout << "There are " << posibilities[changeAmount] << " ways to produce " << changeAmount << " cents change." << endl;
    }

    return 0;
}   // main()
