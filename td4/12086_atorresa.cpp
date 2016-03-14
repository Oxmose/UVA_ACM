#include <iostream> //std::cin std::cout

using namespace std;

//#define DEBUG

inline int erase(int i)
{
    return (i & (i + 1));
}

void initTab(unsigned int *vals, const unsigned int *potmeters, unsigned int potmetersCount)
{
    vals[0] = potmeters[0];
    for(unsigned int i = 1; i < potmetersCount; ++i)
    {
        vals[i] = vals[i - 1] + potmeters[i];
    }
}

void initTabSec(const unsigned int *vals, unsigned int *valsSec,  unsigned int potmetersCount)
{
    valsSec[0] = vals[0];
    for(unsigned int i = 1; i < potmetersCount; ++i)
    {
        int newerase = erase(i);
        if(newerase < 1)
            valsSec[i] = vals[i];
        else
            valsSec[i] = vals[i] - vals[newerase - 1];
    }
}

void set(int x, int inc, unsigned int *vals, unsigned int potmetersCount)
{
    while(x < (int)potmetersCount)
    {
        vals[x] += inc;
        x = (x | (x + 1));
    }
}

int somme(int x, int y, const unsigned *valsSeq)
{
    if(x == 0)
    {
        int res = 0;
        while(y >= 0)
        {
            res += valsSeq[y];
            y = (y & (y + 1)) - 1;
        }
        return res;
    }
    else
        return somme(0, y, valsSeq) - somme(0, x - 1, valsSeq);
}

int main(int argc, char** argv)
{
    // OPTI ON INPUT
    ios_base::sync_with_stdio(false);
    
    unsigned int caseC = 1;

    unsigned int potmetersCount;
    while(cin >> potmetersCount)
    {
        if(potmetersCount == 0) return 0;

        // Read input data
        unsigned int potmeters[potmetersCount];
        for(unsigned int i = 0; i < potmetersCount; ++i)
        {
            cin >> potmeters[i];
        }

        if(caseC != 1)
                cout << endl;

        cout << "Case " << caseC++ << ":" << endl;

        string actionType;

        unsigned int vals[potmetersCount];
        unsigned int valsSec[potmetersCount];
        initTab(vals, potmeters, potmetersCount);
        initTabSec(vals, valsSec, potmetersCount);        
        

        while(cin >> actionType)
        {
            if(actionType == "END") break;
            unsigned int x;
            unsigned int y; 
            cin >> x;
            cin >> y;
            bool init = false;
            
            
            if(actionType[0] == 'M')
            {
                cout << somme(x - 1, y - 1, valsSec) << endl;
            }
            else if(actionType[0] == 'S')
            {
                int inc = y - potmeters[x - 1];
                potmeters[x - 1] = y;
                set(x - 1, inc, valsSec, potmetersCount);               
            }           
        }        
    }
    return 0;
} // main(int, char**)
