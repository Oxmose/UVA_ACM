#include <iostream>

using namespace std;

#define ARE "aDbAD"
#define BRE "GAaGb"

string clear(string &str)
{
	string newString = "";
	unsigned int cpt = 0;
	for(unsigned int i = 0; i < str.size(); ++i)
	{
		if(str[i] != 'a' && str[i] != 'b')
			newString += str[i];
	}
	return newString;
}

void deploy(string &in, long long steps)
{
	string newStr;
    long long realSizeT = 0;
	while(realSizeT < steps)
	{
		newStr = "";
        realSizeT = 0;
        // Generate string
		for(long long i = 0; i < in.size(); ++i)
		{
            if(in[i] != 'D' && in[i] != 'G')
                ++realSizeT;

			if(in[i] == 'a')
			{
				newStr += ARE;
			}
			else if(in[i] == 'b')
			{
				newStr += BRE;
			}                
            else                
				newStr += in[i];

		} 
		in = newStr;
	}
}

void getCoordinates(long long &x, long long &y, const string &str, long long steps)
{
	int orient = 0;
	x = 0;
	y = 0;
	int cpt = 0;
	for(long long i = 0; cpt < steps; ++i)
	{
		if(str[i] == 'A')
		{
			++cpt;
			switch(orient)
			{
				case 0:
					++y;
					break;
				case 1:
					++x;
					break;
				case 2:
					--y;
					break;
				case 3:
					--x;
					break;
			}
		}
		else if(str[i] == 'D')
		{
			orient = (orient + 1) % 4;
		}
		else if(str[i] == 'G')
		{
			if(--orient < 0)
				orient = 3;
		}
	}
}

int main()
{
	
	long long n;
	string init = "Aa";
	while(cin >> n)
	{
		deploy(init, n);
		string cleared = clear(init);
		long long x, y;
		getCoordinates(x, y, cleared, n);		
		cout << x << " " << y << endl;
	}	
	return 0;
}
