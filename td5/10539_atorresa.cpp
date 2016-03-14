#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1000000000000
#define MAXPRIME 1000000

vector<long long> primes;
vector<long long> aPrimes;

void getAPrimesOf(long long prime)
{
    long long value = prime;
    while((value = value * prime) < MAX)
        aPrimes.push_back(value);
}

void buildPrimesMy()
{
    if(primes.size() < 1)
    {
        primes.push_back(2);
        getAPrimesOf(2);
    }
    for(long long i = 3; i < MAXPRIME; i += 2)
    {
        bool found = false;
        for(long long j = 1; j < primes.size(); j++)
        {
            if(i % primes[j] == 0)
            {
                found = true;
                break;
            }
            if(primes[j] >= sqrt(i))
                break;
        }

        if(found) continue;

        primes.push_back(i);
        getAPrimesOf(i);
    };
}

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int cases;
    cin >> cases;

    buildPrimesMy();
    sort(aPrimes.begin(), aPrimes.end());
    
    while(cases > 0)
    {
	    long long low;
        long long high;
        cin >> low;
	    cin >> high;

        long long count = 0;
        /*long long newlow = 0;
        

        for(long long i = 0; aPrimes[i] < low; ++i)
            newlow = i; */
       
        for(long long i = 0; aPrimes[i] < high; ++i)
        {
            if(aPrimes[i] >= low)
                ++count;
        }
        cout << count << endl;
    	--cases;
    }
    return 0;
} // main()
