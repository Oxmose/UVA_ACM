#include <iostream>	//std::cout
#include <string>	//std::string
#include <sstream>	//std::strinstream

using namespace std;

int main()
{
	string line;
	
	// Read each line
	while(getline(cin, line))
	{
		stringstream tmp(line);

		// Store values
		unsigned long long fstval;
		unsigned long long scdval;		
		tmp >> fstval >> scdval;

		// Make test and output	
		cout << ((fstval < scdval) ? scdval - fstval : fstval - scdval) << endl;
	}
	return 0;
} // main()
