#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct line
{
    double xa;
    double xb;
    double ya;
    double yb;

    bool v;
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed;
    cout << setprecision(3);

    double x;
    double y;
    double c;

    while(cin >> x)
    {
        cin >> y;
        cin >> c;

        double min = 0.001;
        double max = y;

        while(max - min > 0.0001)
        {
            double inter = (min + max) / 2;
            double interSq = inter * inter;

            double height = sqrt(x * x - interSq);
            double width = sqrt(y * y - interSq);

            struct line line1;
            struct line line2;

            line1.xa = 0;
            line1.ya = height;
            line1.xb = inter;
            line1.yb = 0;

            line2.xa = 0;
            line2.ya = 0;
            line2.xb = inter;
            line2.yb = width;

            line1.v = (line1.xa == line1.xb);
            line2.v = (line2.xa == line2.xb);

            double m1, orig1;
            double m2, orig2;

            if(line1.v)
            {
                m1 = 99999;
                orig1 = line1.xa;
            }
            else
            {
                m1 = (line1.yb - line1.ya) / (line1.xb - line1.xa);
                orig1 = line1.ya - line1.xa * m1;
            }

            if(line2.v)
            {
                m2 = 99999; 
                orig2 = line2.xa;
            }
            else
            {
                m2 = (line2.yb - line2.ya) / (line2.xb - line2.xa);
                orig2 = line2.ya - line2.xa * m2;
            }

            double hc;
            if(line1.v)
            {
                hc = orig1;
            }
            else
            {
                hc = ((orig1 - orig2) / (m2 - m1)) * m1 + orig1;
            }
            if(hc > c)
                min = inter;
            else 
                max = inter;
        }

        cout << (min + max) / 2 << endl;
    }
    return 0;
}
