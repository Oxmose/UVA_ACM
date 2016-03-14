#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    
    unsigned long int x;
    unsigned long int y;
    unsigned int n;

    unsigned int dataSetsCount;
    cin >> dataSetsCount;

    unsigned int cpt = 0;

    while(cin >> x && cpt < dataSetsCount)
    {
        if(x == 0)
            return 0;

        cin >> y;
        cin >> n;

        unsigned long int result = 1;
        // Fast expo method as seen in ASR1
        while(y > 0)
        {
            if((y % 2) == 1)
            {
                result = ((result % n) * (x % n)) % n;
                --y;
            }
            x = ((x % n) * (x % n)) % n;
            y /= 2;
        }
        cout << result % n << endl;
        ++cpt;
    }
    return 0;
} // main()
