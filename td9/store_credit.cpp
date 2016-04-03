#include <iostream>
 #include <vector>
 
 using namespace std;
 
 int main()
 {   
     int cases;
     cin >> cases;
     cases = 1;
     int credit;
     int objects;
     while(cin >> credit)
     {
         cin >> objects;
         vector<int> prices(objects);
         for(unsigned int i = 0 ; i < objects; ++i)
         {
             cin >> prices[i];
       
         }
 
         for(unsigned int i = 0; i < objects; ++i)
         {
             for(unsigned int j = i + 1; j < objects; ++j)
             {
                 if(prices[i] + prices[j] == credit)
                 {
                     cout << "Case #" << cases++ << ": " << min(i + 1, j + 1) << " " << max(i + 1, j + 1) << endl;
                     i = objects;
                     break;
                 }
             }
         }
     }
     return 0;
 } 
