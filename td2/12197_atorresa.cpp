#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	// Set precision of output
	cout << std::fixed << std::setprecision(9);
	double precision = 1e-9;

	// OPTI
	ios_base::sync_with_stdio(false);
	unsigned int housesCount;
	bool firstRead = true;
	while(cin >> housesCount)
	{

		// Init data
		// Set range for our distance (-200000 <= x,y <= 200000)
		double rangeMin = -200000;
		double rangeMax = 200000;

		// The middle will help us to determine which side of the range we want to shrink
		double rangeMinCrusor;
		double rangeMaxCursor;

		// Distance from the chosen point and the more far house
		double maxDistance = 0;
		double maxDistance2 = 0;

		if(housesCount == 0)
			return 0;

		if(firstRead)
			firstRead = false;
		else
			cout << endl;

		double housesCoordinates[housesCount][2];
		// Read houses coordinates
		for(unsigned int i = 0; i < housesCount; ++i)
		{
			cin.ignore();
			cin >> housesCoordinates[i][0];
			cin >> housesCoordinates[i][1];
		}
		cin.ignore();

		// Verify the precision we want
		while(precision < abs(rangeMin - rangeMax))
		{
			// Compute the middle of the left and right side of range
			rangeMinCrusor = (rangeMax + rangeMin) / 2;
			rangeMaxCursor = (rangeMinCrusor + rangeMax) / 2;

			// Get the max distance from the chosen point (Min side)
			double max = 0;
			for(unsigned int i = 0; i < housesCount; ++i)
			{
				double value = (housesCoordinates[i][0] - rangeMinCrusor) * (housesCoordinates[i][0] - rangeMinCrusor) + (housesCoordinates[i][1] * housesCoordinates[i][1]);
				if(max < value)
					max = value;
			}
			maxDistance = max;
			max = 0;
			// Get the max distance from the chosen point (Max side)
			for(unsigned int i = 0; i < housesCount; ++i)
			{
				double value = (housesCoordinates[i][0] - rangeMaxCursor) * (housesCoordinates[i][0] - rangeMaxCursor) + (housesCoordinates[i][1] * housesCoordinates[i][1]);
				if(max < value)
					max = value;
			}
			maxDistance2 = max;

			// If max side is more far than the min side we shrin
			if(maxDistance2 > maxDistance)
				rangeMax = rangeMaxCursor;
			else
				rangeMin = rangeMinCrusor;
		}

		maxDistance = sqrt(maxDistance);
		cout << rangeMinCrusor <<  " " << maxDistance;
	}

	return 0;
} // main()
