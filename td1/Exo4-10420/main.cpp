#include <iostream>	//std::cout
#include <string>	//std::string
#include <sstream>	//std::stringstream
#include <map>		//std::map

using namespace std;

int main()
{
	string line;

	// First line is useless, but let's use it as simple control
	getline(cin, line);
	stringstream converter(line);
	unsigned int lineCount;
	converter >> lineCount;

	// Let's use a map to store the countries and associated conquests
	map<string, unsigned int> conquestsMap;
	unsigned int counter = 0;

	// Parse the fuile
	while(getline(cin, line) && counter < lineCount)
	{
		stringstream splitter(line);

		// Retrive the key (country)
		string key;
		splitter >> key;

		// Add key if doesn't exists
		if(conquestsMap.find(key) == conquestsMap.end())
			conquestsMap.emplace(key, 1);
		else
			conquestsMap.at(key) = conquestsMap.at(key) + 1;

		++counter;
	}

	// Display result
	for(pair<string, unsigned int> entry : conquestsMap)
	{
		cout << entry.first << " " << entry.second << endl;
	}
	return 0;
} // main()
