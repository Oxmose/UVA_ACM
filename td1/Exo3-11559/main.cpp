#include <iostream>	//std::cout
#include <string>	//std::string
#include <sstream>	//std::stringstream

using namespace std;

int main()
{
	string line;

	// Read lines by lines
	while(getline(cin, line))
	{

		stringstream splitter(line);

		// Loading data for the current instance
		unsigned int registered;
		unsigned int budget;
		unsigned int hotels;
		unsigned int possibleWeeks;

		// Split the line to retreive data
		splitter>> registered >> budget >> hotels >> possibleWeeks;

		unsigned int hotelsPrices[hotels];
		unsigned int availableRooms[hotels][possibleWeeks];

		// Loading hotels data for the current instance
		for(unsigned int i = 0; i < hotels; ++i)
		{
			// Get price for a night at the hotel i
			getline(cin, line);
			stringstream conv(line);
			conv >> hotelsPrices[i];

			// Get available rooms
			getline(cin, line);
			stringstream convLine(line);
			for(unsigned int j = 0; j < possibleWeeks; ++j)
			{
				convLine >> availableRooms[i][j];
			}
		}

		// Process data
		unsigned int cost = 0;
		bool init = false;
	
		// Browse each hotels
		for(unsigned int i = 0; i < hotels; ++i)
		{
			// Test if there are enought beds
			for(unsigned int j = 0; j < possibleWeeks; ++j)
			{
				// If hotels allows us to book rooms
				if(availableRooms[i][j] >= registered)
				{
					// Save lowest price
					unsigned int price = hotelsPrices[i] * registered;
					if(budget >= price && (cost > price || init == false))
					{
						init = true;
						cost = price;
					}
				}
			}
		}

		// Output depending on the result of the data preocessing
		if(cost)
			cout << cost << endl;
		else
			cout << "stay home" << endl;
	}

	return 0;
} // main()
