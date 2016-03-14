#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int serials;
    unsigned int cases;
    cin >> cases;

    while(cases > 0 && cin >> serials)
    {
    	long maxValue = 0;
    	long pgcd = 0;
    	long buffer;
    	long value;

    	while(serials)
    	{
    		value = 0;

    		for(unsigned int i = 0; i < 10; ++i)
    		{
    			cin >> buffer;
    			if(i == 9)
    				value -= buffer;
    			else
    				value += buffer;
    		}

    		if(buffer > maxValue)
    			maxValue = buffer;

    		while(value)
    		{
    			long rest = pgcd % value;
    			pgcd = value;
    			value = rest;
    		}
    		--serials;
    	}

    	if(maxValue >= pgcd)
    		pgcd = 0;

    	if(pgcd > 1)
    		cout << pgcd << endl;
    	else
    		cout << "impossible" << endl;

    	--cases;
    }
    return 0;
} // main()
