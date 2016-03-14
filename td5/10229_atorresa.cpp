#include <iostream>

using namespace std;

unsigned int fibo[2];
unsigned int expM;

unsigned int exp(unsigned int n, unsigned int m)
{
    unsigned long int result = 1;
    while(m > 0)
    {
        if((m % 2) == 1)
        {
            result *= n;
            --m;
        }
        n *=  n;
        m /= 2;
    }
    return result;
}

// We use fast fibonacci doubling method 
void doublingFib(unsigned long long int n)
{
    unsigned long long int fn;
    unsigned long long int fn1;
    unsigned long long int f2n;
    unsigned long long int f2n1;

    if(n == 0)
    {
        fibo[0] = 0;
        fibo[1] = 1 % expM;
        return;
    }

    doublingFib(n / 2);

    // We need n - 1 and n - 2 values
    fn = fibo[0];
    fn1 = fibo[1];

    /* PARITY MANAGEMENT */

    // Compute (n - 1) * (2 (n - 2) - (n - 1)
    f2n = fn * (2 * fn1 - fn);
    // Compute (n - 1)^2 + (n - 2)^2
    f2n1 = (fn * fn + fn1 * fn1);

    // If odd
    if(n & 1)
    {
        fibo[0] = f2n1 % expM;
        fibo[1] = (f2n + f2n1) % expM;
        
    }
    // If even
    else
    {
        fibo[0] = f2n % expM;
        fibo[1] = f2n1 % expM;
    } 
}

int main()
{
    ios_base::sync_with_stdio(false);
    
    unsigned int n, m;

    while(cin >> n)
    {
        cin >> m;
        fibo[0] = 0;
        expM = exp(2, m); 
        doublingFib(n);
	cout << fibo[0] << endl;
    }
    return 0;
} // main()
