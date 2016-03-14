#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* OPTI */
vector<unsigned int> primeOne    	= {2, 4, 6, 10, 12, 16};
vector<unsigned int> primeTwo   	= {1, 3, 5, 9, 11, 15};
vector<unsigned int> primeThree 	= {2, 4, 8, 10, 14, 16};
vector<unsigned int> primeFour  	= {1, 3, 7, 9, 13, 15};
vector<unsigned int> primeFive		= {2, 6, 8, 12, 14};
vector<unsigned int> primeSix		= {1, 5, 7, 11, 13};
vector<unsigned int> primeSeven		= {4, 6, 10, 12, 16};
vector<unsigned int> primeEight		= {3, 5, 9, 11, 15};
vector<unsigned int> primeNine 		= {2, 4, 8, 10, 14};
vector<unsigned int> primeTen		= {1, 3, 7, 9, 13};
vector<unsigned int> primeEleven 	= {2, 6, 8, 12};
vector<unsigned int> primeTwelve	= {1, 5, 7, 11};
vector<unsigned int> primeThirt		= {4, 6, 10, 16};
vector<unsigned int> primeFourt		= {3, 5, 9, 15};
vector<unsigned int> primeFift		= {2, 4, 8, 14, 16};
vector<unsigned int> primeSixt		= {1, 3, 7, 13, 15};

vector<vector<unsigned int>> primes;

unsigned int value;

int counter = 0;

// We will backtrack all the possible value thanks to this recursicve function
void primesOf(unsigned int number, vector<unsigned int> alreadyTaken, unsigned int step)
{
    // If we reached the amount of numbers to put in the cycle
	if(step >= value)
	{
		for(unsigned int i = 0; i < alreadyTaken.size(); ++i)
		{
			if(i < alreadyTaken.size() - 1)
				cout << alreadyTaken[i] << " ";
			else
				cout << alreadyTaken[i] << endl;
		}

		return;
	}


	vector<unsigned int> thisStep;
    // For each possibilities, we will test and add them to the list of next possibbilites to test
	for(unsigned int i = 0; i < primes[number - 1].size(); ++i)
	{
        // if the posibility i > than the current last value and has no been taken
		if(primes[number - 1][i] <= value && find(alreadyTaken.begin(), alreadyTaken.end(), primes[number - 1][i]) == alreadyTaken.end())
		{
            // If we are achieving the last step, we need to check if this posibility is also a posibility for 1
			if(step == value - 1)
			{ 
				if(find(primes[alreadyTaken[0] - 1].begin(), primes[alreadyTaken[0] - 1].end(), primes[number - 1][i]) != primes[alreadyTaken[0] - 1].end())
				{
					thisStep.push_back(primes[number - 1][i]);
				}
			}
			else
				thisStep.push_back(primes[number - 1][i]);
		}
	}

	// For each posibilities, just run this process again 
	for(unsigned int i = 0; i < thisStep.size(); ++i)
	{
		vector<unsigned int> tmp = alreadyTaken;
		tmp.push_back(thisStep[i]);
		primesOf(thisStep[i], tmp, step + 1);
	}
}

int main()
{
	// OPTI
	ios_base::sync_with_stdio(false);

	primes.push_back(primeOne);
	primes.push_back(primeTwo);
	primes.push_back(primeThree);
	primes.push_back(primeFour);
	primes.push_back(primeFive);
	primes.push_back(primeSix);
	primes.push_back(primeSeven);
	primes.push_back(primeEight);
	primes.push_back(primeNine);
	primes.push_back(primeTen);
	primes.push_back(primeEleven);
	primes.push_back(primeTwelve);
	primes.push_back(primeThirt);
	primes.push_back(primeFourt);
	primes.push_back(primeFift);
	primes.push_back(primeSixt);


	unsigned int curCase = 1;
	while(cin >> value)
	{
		if(curCase != 1)
			cout << endl;
		vector<unsigned int> alreadyTaken;
		alreadyTaken.push_back(1);

		cout << "Case " << curCase << ":" << endl;
		primesOf(1, alreadyTaken, 1);
		++curCase;
	}

	return 0;
} // main()
