#include <iostream>
#include <cstring>

//#define DEBUG

using namespace std;

bool data[100][100];
bool solved = false;
unsigned short int choice[100];
unsigned short int enclosuresNumber;

// Gain time with atoi
int fast_atoi( const char * str )
{
    int val = 0;
    while( *str ) {
        val = val*10 + (*str++ - '0');
    }
    return val;
}

// Color the graph
void solve(unsigned short int step)
{    
    // If we colored everything
    if(step == enclosuresNumber + 1)
    {
        solved = true;
        return;
    }
    // Set of already used color (0 = none)
    bool alreadyplaced[5] = {false, false, false, false, false};
    for(unsigned short int j = 0; j < step; ++j)
        if(data[step][j])
            alreadyplaced[choice[j]] = true;

    bool placed = false;
    // For each color
    for(unsigned short int j = 0; j < 4; ++j)
    {
        // If this color can be aplied
        if(!alreadyplaced[j])
        {
            // Apply and recurse
            choice[step] = j;
            solve(step + 1);
            if(solved)
                return;
        }
    } 
}

int main()
{
    bool fst = true;
    ios_base::sync_with_stdio(false);
    while(cin >> enclosuresNumber)
    {        

        solved = false;
        memset(choice, 4, sizeof(choice));
        memset(data, false, sizeof(data));
        
        cin.ignore();
        string line;
        while(getline(cin, line))
        {
            if(line.empty())
                break;

            string value;
            int index;
            for(unsigned int i = 0; i < line.size(); ++i)
            {
                if(line[i] == '-')
                {
                    index = fast_atoi(value.c_str());
                    value = "";
                }
                else
                    value += line[i];
            }
            // Create graph as a matrix
            int val = fast_atoi(value.c_str());
            data[index - 1][val - 1] = true;
            data[val - 1][index - 1] = true;
        }

        solve(0);

        if(!fst)
            cout << endl;
        fst = false;

        for(unsigned short int i = 0; i < enclosuresNumber; ++i)
            cout << i + 1 << " " << choice[i] + 1 << endl;
    }
    return 0;
} // main()
