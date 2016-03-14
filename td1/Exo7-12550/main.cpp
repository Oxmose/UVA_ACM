#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Used a function in case we want ot introduce more complex equations
inline double compute(double x, double y, double factor1, double factor2)
{
    return x * factor1 + y * factor2;
}// inline compute(double, double, double, double)

// Solver for linear equations
inline pair<double, double> solveLinear(double a, double b, double c, double d)
{
    double deter = a*c - b * b;
    double factor1 = (c*c - b*d) / deter;
    double factor2 = (a*d - c*b) / deter;

    return make_pair(factor1, factor2);
}// inline solveLinear(double, double, double, double)

int main()
{
    string line;

    // One case per line
    while(getline(cin, line))
    {
        stringstream splitter(line);
        double distanceFromWaterfall;
        double jumpingPower;

        splitter >> distanceFromWaterfall >> jumpingPower;

        // Get water speed data
        vector<double> speed;
        double number;
        while(splitter >> number)
            speed.push_back(number);

        // First detect if the pattern is unknown
        if(speed.size() == distanceFromWaterfall + 1)
        {
            // If seed is too high at any points
           // Since it is a non decreasing sequence, just test the first value
           if(speed[0] > jumpingPower)
           {
               cout << "The spider is going to fall!" << endl;
               continue;
           }

            // Can't detect the waterfall
            if(speed[speed.size() - 1] <= jumpingPower)
            {
                cout << "The spider may fall!" << endl;
                continue;
            }

            // Compute the minimum distance
            for(int i = speed.size() - 1; i >= 0; --i)
            {
                if(speed[i] <= jumpingPower)
                {
                    cout << speed.size() - i - 1<< endl;
                    break;
                }
            }
        }
        else
        {
            pair<double, double> coefs = solveLinear(speed[0], speed[1], speed[2], speed[3]);

            // enlarge our data set
            for (unsigned int i = speed.size(); i < distanceFromWaterfall + 1; ++i)
            {
                speed.push_back(compute(speed[i-2], speed[i-1], coefs.first, coefs.second));

                if(jumpingPower < speed[i])
                    break;
            }

            unsigned int distance = 0;
            for (unsigned int i = 0; i < distanceFromWaterfall + 1; ++i)
            {
                if (jumpingPower < speed[i])
                    break;
                ++distance;
            }

            if(distance == 0)
                cout << "The spider is going to fall!" << endl;
            else if(distance == distanceFromWaterfall + 1)
                cout << "The spider may fall!" << endl;
            else
                cout << distanceFromWaterfall - distance + 1 << endl;
        }
    }
    return 0;
} // main()
