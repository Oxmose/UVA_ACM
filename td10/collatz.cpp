#include <iostream>
#include <vector>

using namespace std;

unsigned int fill(vector<long long> &vals, unsigned int to, unsigned int val)
{	
	// If We already computed the value
	if(val < vals.size() && vals[val] != 0)
		return vals[val];

	// New value start at 1
	long long start = 1;
	
	// Test aprity
	if(val % 2 != 0)
		start = fill(vals, to, 1 + 3 * val) + 1;
	else
		start = fill(vals, to, val / 2) + 1;		

	// If we are in the range
	if(val < vals.size())
		vals[val] = start;
	
	return start;
}

int main()
{
	int maxOut = 0;
	int m, n;

	while(cin >> n)
	{
		cin >> m;
				
		int min, max;
		if(n > m)
		{
			min = m;
			max = n;
		}
		else
		{
			min = n;
			max = m;
		}
		vector<long long> vals(max + 1, 0);
		vals[1] = 1;

		// Fill the tab
		for(unsigned int i = min; i <= max; ++i)
			fill(vals, min, i);

		// Get max
		for(unsigned int i = min; i <= max; ++i)
		{
			if(maxOut < vals[i])
				maxOut = vals[i];
		}

		cout << n << " " << m << " " << maxOut << endl;
		maxOut = 0;
	}
	
	return 0;
}
