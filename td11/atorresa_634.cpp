#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int vertices;
    while(cin >> vertices)
    {
        if(vertices == 0) return 0;

        vector<pair<int, int>> points;
        int cpt = vertices;
        int x, y;
        while(cpt)
        {
            cin >> x >> y;  
            points.push_back(make_pair(x, y));   
            --cpt;       
        }
        pair<int, int> point;
        cin >> point.first >> point.second;
        int cross = 0;
        while(point.first < 10001)
        {
            for(unsigned int i = 0; i < points.size(); ++i)
            {
                if(points[i].first == point.first)
                {
                    if(points[i].second > point.second && points[i + 1 % vertices].second < point.second)
                        ++cross;
                    else if(points[i].second < point.second && points[i + 1 % vertices].second > point.second)
                        ++cross;
                }
            }

            ++point.first;
        }
        if(cross % 2)
            cout << "T" << endl;
        else
            cout << "F" << endl;
    }
	return 0;
}
