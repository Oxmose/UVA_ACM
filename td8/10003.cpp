#include <iostream>
#include <map>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

map< tuple<int, int, int, int>, int > fait;



int opt(const int &start,  const int &end, const vector<int> &cuts, const int &begtab, const int &endtab)
{
	if(endtab == begtab)
	{
		return end - start;
	}
	
	int res = opt(cuts[begtab], end, cuts, begtab + 1, endtab) + end - start;
	for(int i = begtab + 1; i < endtab; ++i)
	{		
		int rA, rB;
		rA = fait[make_tuple(start, cuts[i], begtab, i - 1)];
		if (rA == 0) {
			fait[make_tuple(start, cuts[i], begtab, i - 1)] = opt(start, cuts[i], cuts, begtab, i - 1);
			rA = fait[make_tuple(start, cuts[i], begtab, i - 1)];
		}
		rB = fait[make_tuple(cuts[i], end, i + 1, endtab)];
		if (rB == 0) {
			fait[make_tuple(cuts[i], end, i + 1, endtab)] = opt(cuts[i], end, cuts, i + 1, endtab);	
			rB = fait[make_tuple(cuts[i], end, i + 1, endtab)];
		}
		res = min(res, rA + rB + end-start);
	}
	return res;
}

int main()
{
	int lenght;
	while(cin >> lenght)
	{
		fait.clear();
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
