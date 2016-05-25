#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <climits>
#include <stack>
#include <tuple>

using namespace std;

void Levenshtein(string &fst, string &snd)
{
    int l[fst.size() + 1][snd.size() + 1];
    for(unsigned int i = 0; i < fst.size() + 1; ++i)
    {
        l[i][0] = i;
    }
    for(unsigned int i = 0; i < snd.size() + 1; ++i)
    {
        l[0][i] = i;
    }

    int c;
    int oldmin = 0;
    for(unsigned int i = 1; i < fst.size() + 1; ++i)
    {
        for(unsigned int j = 1; j < snd.size() + 1; ++j)
        {
            c = fst[i - 1] != snd[j - 1];
            
            int choice = 0;
            int min = l[i - 1][j] + 1;

            if(l[i][j - 1] + 1 < min)
            {
                min = l[i][j - 1] + 1;
                choice  = 1;
            }
            if(l[i - 1][j - 1] + c < min)
            {
                choice = 2;
                min = l[i - 1][j - 1] + c;
            }

            l[i][j] = min;
        }
    }

    unsigned int i = fst.size();
    unsigned int j = snd.size();
    int min = l[i][j];
    
    int step = 1;

    cout << min << endl;
    while(i || j)
    {
        int newmin = INT_MAX;
        
        if(fst[i - 1] == snd[j - 1])
        {
            --i;
            --j;
            continue;
        }

        if(i > 0 && l[i - 1][j] + 1 == l[i][j])
        {
            newmin = l[i - 1][j];
            cout << step++ << " Delete " << i << endl;
            --i;
            fst.erase(i, 1);
            //continue;
        }

        else if(j > 0 && l[i][j - 1] + 1 == l[i][j])
        {
            newmin = l[i - 1][j];
            cout << step++ << " Insert " << i + 1 << "," << snd[j - 1] << endl;
            --j;
            fst.insert(i, 1, snd[j]);
            //continue;
        }

        else if(i > 0 && j > 0)
        {
            newmin = l[i - 1][j];
            cout << step++ << " Replace " << i << "," << snd[j - 1] << endl;
            --i;
            --j;
            fst[i] = snd[j];
            //continue;
        }
    }
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string fst, snd;
    bool fste = true;
    while(cin >> fst)
    {
        if(!fste)
            cout << endl;
        fste = false;
        cin >> snd;
        Levenshtein(fst, snd);
    }

    return 0;
}
