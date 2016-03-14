#include <iostream>
#include <stdio.h>
#include <string.h>
//#define DEBUG

using namespace std;

// Init the optimal matrix we have to use
int Opt[200][200][20];

// Set of element we can choose
int set[200];

// Settings for each instances
int N;
int M;
int D;

/*
 * Define i : step i
 * j : sum of all the selected number at step i
 * number[i] : element with index i in the set
 * k : count of selected element at step i
 *
 * Opt(i, j, k) = Opt(i + 1, (number[i] + j) mod D, k + 1) + Opt(i + 1, j % D, k)
 *
 * Where : Opt(i + 1, (number[i] + j) mod D, k + 1)  is the opt for next step and we seleted number[i] at step i
 * Opt(i + 1, j % D, k) is the opt for next step and we didn't selected any number of the set at step i
 */
int solveOpt(int i, int j, int k)
{
    // If we reached the maximum amount of selected numbers (M)
    if(k >= M)
    {
        // If the sum of all the numbers is divisible by D then add one possibility
        // (j = a % D, where a is j before the last sum).
        if(j == 0)
            return 1;
        else
            return 0;
    }
    // If we tried all the possible number but 
    if(i >= N)
        return 0;

    // If the case we try to access has already been accessed, do not compute it again
    // (solved my time limit exceeded error)
    if(Opt[i][j][k] != -1)
        return Opt[i][j][k];

    // Else apply the formula
    Opt[i][j][k] = solveOpt(i + 1, (set[i] + j) % D, k + 1) + solveOpt(i + 1, j % D, k);

    return Opt[i][j][k];
} 

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned int setCount = 0;
    unsigned int Q;
    while(cin >> N)
    {
        cin >> Q;

        if(N == 0 && N == Q)
            return 0;

        unsigned short int queries[Q][2];

        // Data input read
        for(unsigned int i = 0; i < N; ++i)
            cin >> set[i];

        for(unsigned int i = 0; i < Q; ++i)
        {
            cin >> queries[i][0];
            cin >> queries[i][1];   
        }
        
        ++setCount;

        cout << "SET " << setCount << ":" << endl;
        for(unsigned int i = 0; i < Q; ++i)
        {
            D = queries[i][0];
            M = queries[i][1];

            cout << "QUERY " << i + 1 << ": ";       

            // Init our matrix with -1 
            // It enable us to avoid computing the same value more than once.
	        for(unsigned int n = 0; n < 200; ++n)
            {
		        for(unsigned int j = 0; j < 200; ++j)
                {
		            for(unsigned int k = 0; k < 20; ++k)
			        {
                        Opt[n][j][k] = -1;
                    }
                }
            }
            // Solve the problem
            cout << solveOpt(0, 0, 0) << endl;
        }
    }
	return 0;
} // main()

//#undef DEBUG
