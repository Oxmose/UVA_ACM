#include <iostream>
#include <map>
#include <vector>

using namespace std;

int opt(int start, int end, vector<int> &cuts, int begtab, int endtab)
{
	if(endtab == begtab)
	{
		return end - start;
	}
	
	int res = opt(cuts[begtab], end, cuts, begtab + 1, endtab) + end - start;
	for(int i = begtab + 1; i < endtab; ++i)
	{		
		res = min(res, opt(start, cuts[i], cuts, begtab, i - 1) + opt(cuts[i], end, cuts, i + 1, endtab) + end - start);
	}
	return res;
}

int main()
{
	int lenght;
	while(cin >> lenght)
	{
		
		if(lenght == 0)
			return 0;
		int n, val;
		cin >> n;
		if(n == 0)
		{
			cout << "The minimum cutting is " << lenght << "." << endl;
			continue;
		}

		vector<int> cut;
		for(unsigned int i = 0; i < n; ++i)
		{
			cin >> val;
			cut.push_back(val);
		}
		int min = opt(0, lenght, cut, 0, cut.size() - 1);
		cout << "The minimum cutting is " << min << "." << endl;
	}
	return 0;
}
