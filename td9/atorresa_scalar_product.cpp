#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
   int cases;
   cin >> cases;
   cases = 1;
   int degree;
   while(cin >> degree)
   {
       vector<long long int> fst(degree);
       vector<long long int> snd(degree);

       for(unsigned int i = 0; i < degree; ++i)
           cin >> fst[i];
       for(unsigned int i = 0; i < degree; ++i)
           cin >> snd[i];
       sort(fst.begin(), fst.end());
       sort(snd.begin(), snd.end());

       long long int min = 0;
       for(unsigned int i = 0; i < degree; ++i)
       {
           min += fst[i] * snd[degree - i - 1];
       }
       cout << "Case #" << cases++ << ": " << min << endl;
   }
   return 0;
}

