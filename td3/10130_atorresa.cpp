#include <iostream>

using namespace std;

int main()
{
	// OPTI
	ios_base::sync_with_stdio(false);

	/*
	*	Let's use the algorithm we saw in ALGO1!!!
	*
	*/

	// Get number of cases
	short unsigned int casesCount;
	cin >> casesCount;
	while(casesCount)
	{

		// Get number of objects
		short unsigned int objectsCount;
		cin >> objectsCount;
		short unsigned int objects[objectsCount][2];

		for(short unsigned int i = 0; i < objectsCount; ++i)
		{
			// Get price an weight
			cin >> objects[i][0];
			cin >> objects[i][1];
		}

		// Get people count
		short unsigned int people;
		cin >> people;
		short unsigned int peopleCarryCap[people];

		short unsigned int capaMax = 0;
		for(short unsigned int i = 0; i < people; ++i)
		{
			cin >> peopleCarryCap[i];
			if(peopleCarryCap[i] > capaMax)
				capaMax = peopleCarryCap[i];
		}

		// We will create a matrix with objct id on lines and 
		// each possible capacities on columns
		unsigned int opt[objectsCount + 1][capaMax + 1];
		for(short unsigned i = 0; i < objectsCount + 1; ++i)
			opt[i][0] = 0;

		for(short unsigned i = 0; i < capaMax + 1; ++i)
			opt[0][i] = 0;

		// Then for each object sand capacities
		for(short unsigned int i = 1; i <= objectsCount; ++i)
		{
			for(short unsigned int j = 1; j <= capaMax; ++j)
			{
				// If we can take the object
				if(j >= objects[i - 1][1])
					// Take the object, add its price when the capacity enable you to take it
					opt[i][j] = max(objects[i - 1][0] + opt[i - 1][j - objects[i - 1][1]], opt[i - 1][j]);					
				else
					// Just put back the object and get the mac price without it
					opt[i][j] = opt[i - 1][j];
			}
		}

		unsigned int maxVal = 0;
		// For each people, get the optimal amount of money they got for their capacity
		for(short unsigned int i = 0; i < people; ++i)
			maxVal += opt[objectsCount][peopleCarryCap[i]];

		cout << maxVal << endl;
		--casesCount;
	}

	return 0;
} // main()
