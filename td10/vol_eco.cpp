#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

#define UP 60
#define STAY 30
#define DOWN 20

int opt[10][1000];
int windVals[10][1000];

void getOpt(int interval)
{
    opt[0][0] = 0;

    for(unsigned int i = 1; i < interval; ++i)
    {
        for(unsigned int j = 1; j < 10; ++j)
        {
            //if(j != 0 && opt[j][i] == 0)
                //break;
        
            int stay = INT_MAX / 2;
            int up = INT_MAX / 2;
            int down = INT_MAX / 2;

            
            stay = opt[j][i - 1] + STAY - windVals[j][i - 1];
            up = opt[j - 1][i - 1] + UP - windVals[j - 1][i - 1];
            if(j < 9)
                down = opt[j + 1][i - 1] + DOWN - windVals[j + 1][i - 1];
        
            opt[j][i] = min(min(stay, up), down);
        }
    }
    // Land
    opt[0][interval] = opt[1][interval - 1] + DOWN - windVals[1][interval - 1];
}



int main()
{
    int N;
    cin >> N;

    bool fst = true;

    int X;
    while(cin >> X)
    {        
        int interval = X / 100;

        for(int i = 9; i >= 0; --i)
        {
            for(int j = 0; j < interval; ++j)
                cin >> windVals[i][j];
        }

	/*for(unsigned int i = 0; i < 10; ++i)
	{
		for(unsigned int j = 0; j < interval; ++j)
			cout << windVals[][i] << " ";
		cout << endl;
	}*/

        for(unsigned int i = 0; i < 10; ++i)
            for(unsigned int j = 0; j < interval; ++j)
                opt[i][j] = INT_MAX / 2;

        getOpt(interval);

        if(fst)
        {
            cout << opt[0][interval] << endl;
            fst = false;
        }
        else
            cout << endl << opt[0][interval] << endl;
        
    }   
    return 0;
}
