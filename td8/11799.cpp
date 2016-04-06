#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int main()
{
	int cases;
	cin >> cases;
	int nextChars;
	int j = 0;
	while(cin >> nextChars)
	{
		j++;
		int val, max;
		max = 0;
		for(unsigned int i = 0; i < nextChars; ++i)
		{
			cin >> val;
			if(max < val)
				max = val;
		}
		cout << "Case " << j << ": " << max << endl; 
	}
	return 0;
}
