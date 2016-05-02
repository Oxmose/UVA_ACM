#include <iostream>
#include <iomanip>

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
    cout << "INTERSECTING LINES OUTPUT" << endl;
    cout << setprecision(2) << fixed;
    int cases;
    cin >> cases;
    while(cases)
    {
        struct line line1;
        struct line line2;

        cin >> line1.xa >> line1.ya >> line1.xb >> line1.yb;
        cin >> line2.xa >> line2.ya >> line2.xb >> line2.yb;

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

        if(m1 == m2 || line1.v && line2.v)
        {
            
            if(orig1 == orig2)
                cout << "LINE" << endl;
            else
                cout << "NONE" << endl;
        }
        else
        {
            double x;
            double y;
            if(line1.v)
            {
                x = orig1;
                y = m2 * x + orig2;
            }
            else if(line2.v)
            {
                x = orig2;
                y = m1 * x + orig1;
            }
            else
            {
                x = (orig1 - orig2) / (m2 - m1);
                y = m1 * x + orig1;
            }
            cout << "POINT " << x << " " << y << endl;
        }
        --cases;
    }
    cout << "END OF OUTPUT" << endl;
    return 0;
}
