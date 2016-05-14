#include <iostream>
#include <vector>

using namespace std;

void opt(int &intervals, int height, int width, vector<vector<int>> &altVals, vector<vector<int>> &optV, int cost)
{
    // Init or quit in case of better cost
    if(optV[height][width] != -1 && optV[height][width] < cost) 
    {
        return;
    }
    else
    {
    	// Save the cost for current step
    	optV[height][width] = cost;
    }


    if(width == intervals + 1) 
    {
        return;
    }
    
    // Try to stay at same alt
    opt(intervals, height, width + 1, altVals, optV, cost - altVals[height][width] + 30);

    // Try to go up if we can
    if(height <= 9)
        opt(intervals, height + 1, width + 1, altVals, optV, cost - altVals[height][width] + 60);

    // Try to go down if we can
    if(height >= 2) 
        opt(intervals, height - 1, width + 1, altVals, optV, cost - altVals[height][width] + 20);
} 

int main()
{
    int N;
    cin >> N;
    int X;
    bool fst = true;
    while(cin >> X)
    {
	if(fst)
	{
		fst = false;
	}
	else
		cout << endl;
        int intervals = X / 100;

        // Altitudes, for convenience added a col and a row
        vector<vector<int>> altVal(11, vector<int>(intervals + 1));
        
        for(unsigned int i = 1; i <= 10; ++i)
        {
            int val;
            for(unsigned int j = 1; j < intervals + 1; ++j)
            {
                cin >> val;
                altVal[11 - i][j] = val;
            }
        }

        vector<vector<int>> optV(11, vector<int>(intervals + 2, -1));

        // Compute opt        
        opt(intervals, 1, 1, altVal, optV, 0);

        // Get opt
        cout << optV[1][intervals + 1] << endl;
    }
    return 0;
}
