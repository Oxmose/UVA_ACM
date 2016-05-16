#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

string Levenshtein(string &fst, string &snd)
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

    int c = 0;
    for(unsigned int i = 1; i < fst.size() + 1; ++i)
    {
        for(unsigned int j = 1; j < snd.size() + 1; ++j)
        {
            if(fst[i - 1] == snd[j - 1])
                c = 0;
            else
                c = 1;
            
            int choice = 0;
            int min = l[i - 1][j] + 1;
            if(l[i][j - 1] + 1 < min)
            {
                min = l[i][j - 1] + 1;
            }
            if(l[i - 1][j - 1] + c < min)
            {
                min = l[i - 1][j - 1] + c;
            }

            l[i][j] = min;
        }
    }

    /*for(unsigned int i = 0; i < fst.size() + 1; ++i)
    {
        for(unsigned int j = 0; j < snd.size() + 1; ++j)
            cout << l[i][j] << " ";
        cout << endl;
    }*/
    string choices("");
    int step = l[fst.size()][snd.size()];

    int i = fst.size();
    int j = snd.size();
    int last = l[fst.size()][snd.size()];
    int min;
    int dec = 0;
    while(i > 0 || j > 0)
    {
        int savei, savej;
        int op = 3;
        if(i - 1 >= 0)
        {
            min = l[i - 1][j];
            op = 1;
            savei = i - 1;
            savej = j;
            ++dec;
        }        

        if(j - 1 >= 0 && i - 1 >= 0 && min > l[i - 1][j - 1])
        {
            min = l[i - 1][j - 1];
            op = 3;
            savei = i - 1;
            savej = j - 1;
        }

        if(j - 1 >= 0 && min > l[i][j - 1])
        {
            min = l[i][j - 1];
            op = 2;
            savei = i;
            savej = j - 1;
        }

        if(last > min)
        {
            last = min;
            if(op == 3)
                choices = to_string(step--) + " Delete " + to_string(savei + 1) + "\n" + choices;
            else if(op == 2)
                choices = to_string(step--) + " Insert " + to_string(savej + 1) + "," + snd[savej] + "\n" + choices;
            else
                choices = to_string(step--) + " Replace " + to_string(savei - dec) + "," + snd[savej - 1] + "\n" + choices;
        }
        i = savei;
        j = savej;
        
    }
    cout << endl;
    
    return to_string(l[fst.size()][snd.size()]) + "\n" + choices.substr(0, choices.size() - 1);
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    string fst, snd;
    while(cin >> fst)
    {
        cin >> snd;
        cout << Levenshtein(fst, snd) << endl;
    }

    return 0;
}
