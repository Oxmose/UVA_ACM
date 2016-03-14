#include <iostream>	//std::cout
#include <sstream>	//std::stringstream
#include <string>	//std::string

using namespace std;

int main()
{
	// Init vars
        string line;
        stringstream result;

	// Flag that determine if we already read the first quote or a pair
        bool fstquote = true;

        // Reading file
        while(getline(cin, line))
        {
		// Read all the line
                for(unsigned int i = 0; i < line.size(); ++i)
                {
			// If we found a quote
                        if(line.at(i) == '"')
                        {
				// Test if first quote or second one
                                fstquote ? result << "``" : result << "''";
                                fstquote = !fstquote;
                        }
                        else
                        {
				// Or just write the character
                                result << line.at(i);
                        }
                }
		// New line feed
                result << '\n';
        }
	// Output the result
        cout << result.str();
        return 0;
} // main()
