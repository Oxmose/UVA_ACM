#include <iostream>
#include <vector>

using namespace std;

struct rectangle
{
    int x1;
    int x2;

    int y1;
    int y2;
};

typedef struct rectangle rectangle;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    int cpt = 0;
    while(cpt++ < cases)
    {
        int surface = 0;
        int rectcpt;
        cin >> rectcpt;

        vector<rectangle> rects;
        for(int i = 0; i < rectcpt; ++i)
        {
            rectangle newrect;
            cin >> newrect.x1 >> newrect.y1 >> newrect.x2 >> newrect.y2;

            rects.push_back(newrect);
        }
        rectangle last;
        last = rects[0];
        surface = 1;
        for(int i = 1; i < rectcpt; ++i)
        {
            int maxXL = max(last.x1, rects[i].x1);
            int minXR = min(last.x2, rects[i].x2);

            if(minXR <= maxXL)
            {
                surface = 0;
                break;
            }
            else
            {
                last.x1 = maxXL;
                last.y1 = max(last.y1, rects[i].y1);
                last.x2 = minXR;
                last.y2 = min(last.y2, rects[i].y2);
            }
        }

        if(surface != 0)
        {
            surface = (last.x2 - last.x1) * (last.y2 - last.y1);
	    if(surface < 0)
		surface = 0;
        }
        
        cout << "Case " << cpt << ": " << surface << endl;        
    }
    return 0;
}
