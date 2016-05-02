#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

#define vect pair<double, double>

struct kingdom
{
    int sitesCount;
    double area;
    bool isAlive;
    vector<vect> sites;
    vector<vect> conArea;
};

vect minusv(vect &v1, vect &v2)
{
    vect v;
    v.first = v1.first - v2.first;
    v.second = v1.second - v2.second;
    return v;
}

double vpro(vect &v1, vect &v2)
{
    return v1.first * v2.second - v1.second * v2.first;
}

void getConArea(kingdom &k, unsigned int i, vector<vect> &hull, unsigned int min)
{
    vect current = k.sites[i];
    while(hull.size() > min)
    {
        vect fst = hull.back(); 
        hull.pop_back(); 
        vect snd = hull.back();
        vect vminus1 = minusv(fst, snd);
        vect vminus2 = minusv(current, snd);
        if(vpro(vminus1, vminus2) > 0) 
        { 
            hull.push_back(fst); 
            break; 
        }
    }
    hull.push_back(current);
}

void getConArea(kingdom &k)
{
    sort(k.sites.begin(), k.sites.end());
    vector<vect> env;
    for(unsigned int i = 0; i < k.sitesCount; ++i)    
        getConArea(k, i, env, 1);

    unsigned int size = env.size();
    for(unsigned int i = k.sitesCount; i > 0; --i)    
        getConArea(k, i - 1, env, size);

    k.conArea = env;
}

vect getCmpConv(kingdom &k, int index)
{
    if(k.conArea.size() == 0)
        getConArea(k);
    return k.conArea[index];
}

double getEnvelop(kingdom &k)
{
    if(k.area < 0)
    {
        k.area = 0;        
        for(unsigned int i = 1; i < k.conArea.size(); ++i)
        {
            vect va = getCmpConv(k, i - 1);
            vect vb = getCmpConv(k, i);
            k.area += vpro(va, vb) / 2;
        }
    }
    return k.area;
}

bool envelop(kingdom &k, double x, double y)
{
    // INIT first time
    getCmpConv(k, 1);
    bool env = true;
    vect inVect = make_pair(x, y);
    
    for(unsigned int i = 1; i < k.conArea.size() && env; ++i)
    {
        vect va = getCmpConv(k, i - 1);
        vect vb = getCmpConv(k, i);
        vect vminus1 = minusv(vb, va);
        vect vminus2 = minusv(inVect, va);
        env = (vpro(vminus1, vminus2) > 0);
    }
    return env;
}

double getArea(kingdom &k, double x, double y)
{
    if(k.isAlive && envelop(k, x, y))
    {
        k.isAlive = false;
        return getEnvelop(k);
    }
    else
        return 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed;
    cout << setprecision(2);

    // Get the kigdoms
    vector<kingdom> kingdoms;
    int sitesCount;
    while(cin >> sitesCount)
    {
        if(sitesCount == -1)
            break;

        struct kingdom newkingdom;
        newkingdom.sitesCount = sitesCount;
        newkingdom.isAlive = true;
        newkingdom.area = -1;

        while(sitesCount)
        {
            vect site;
            cin >> site.first;
            cin >> site.second;

            newkingdom.sites.push_back(site);
            --sitesCount;
        }
        kingdoms.push_back(newkingdom);
    }
    
    // Get the missiles
    double area = 0;
    int x;
    int y;
    while(cin >> x)
    {
        cin >> y;
        for(unsigned int i = 0; i < kingdoms.size(); ++i)           
            area += getArea(kingdoms[i], x, y);
    }

    cout << area << endl;
    return 0;
}
