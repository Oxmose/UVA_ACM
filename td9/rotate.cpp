#include <iostream>
#include <vector>
using namespace std;

void check(int &k, char player, bool &val, vector<vector<char>> &rotBoard)
{
    //Row
    int size = rotBoard.size();
    for(unsigned int i = 0; i < size; ++i)
    {
        int m = 0;
        for(unsigned int j = 0; j < size; ++j)
        {
            if(rotBoard[i][j] == player)
            {
                ++m;
                if(m == k)
                {
                    val = true;
                    return;
                }
            }
            else
                m = 0;
        } 
    }
    // Columns
    for(unsigned int i = 0; i < size; ++i)
    {
        int m = 0;
        for(unsigned int j = 0; j < size; ++j)
        {
            if(rotBoard[j][i] == player)
            {
                ++m;
                if(m == k)
                {
                    val = true;
                    return;
                }
            }
            else
                m = 0;
        }
    }

    // Diag left
    for(unsigned int i = 0; i < size; ++i)
    {        
        for(unsigned int j = 0; j < size; ++j)
        {
            int m = 0;
            int tmpi = i + 1;
            int tmpj = j + 1;
            if(rotBoard[i][j] == player)
            {
                m = 1;
                for(; tmpi < size;)
                {
                    if(rotBoard[tmpi][tmpj] != player)
                    {
                        break;                           
                    }

                    ++m; 
                    if(m == k)
                    {
                        val = true;
                        return;
                    } 
                    ++tmpi;
                    ++tmpj;                              
                }                                
            }
        }                
    }

    // Diag right
    for(unsigned int i = 0; i < size; ++i)
    {        
        for(int j = size - 1; j >= 0; --j)
        {
            int m = 0;
            int tmpi = i + 1;
            int tmpj = j - 1;
            if(rotBoard[i][j] == player)
            {
                m = 1;
                for(; tmpj >= 0 && tmpi < size;)
                {
                    if(rotBoard[tmpi][tmpj] != player)
                    {
                        break;                           
                    }

                    ++m; 
                    if(m == k)
                    {
                        val = true;
                        return;
                    } 
                    ++tmpi;
                    --tmpj;                              
                }                                
            }
        }                
    }
}

int main()
{
    int cases;
    cin >> cases;
    cases = 1;
    int size, k; 
    while(cin >> size)
    {
        cin >> k;
        vector<vector<char>> board(size, vector<char>(size));
        for(unsigned int i = 0; i < size; ++i)
            for(unsigned int j = 0; j < size; ++j)
                cin >> board[i][j];
        vector<vector<char>> rotBoard(size, vector<char>(size));
        for(int i = size - 1; i >= 0; --i)
            for(unsigned int j = 0; j < size; ++j)
                rotBoard[size - i - 1][size - j - 1] = board[j][size - i - 1];

        for(int i = size - 2; i >= 0; --i)
        {
            for(unsigned int j = 0; j < size; ++j)
            {
                if(rotBoard[i][j] != '.')
                {
                    int tmp = i;
                    while(tmp < size - 1 && rotBoard[tmp + 1][j] == '.')
                    {                      
                        rotBoard[tmp + 1][j] = rotBoard[tmp][j];
                        rotBoard[tmp][j] = '.';
                        ++tmp;
                    }
                }
            }
        }
        bool R = false;
        bool B = false;

        check(k, 'R', R, rotBoard);
        check(k, 'B', B, rotBoard);

        /*for(unsigned int i = 0; i < size; ++i)
        {
            for(unsigned int j = 0; j < size; ++j)
                cout << rotBoard[i][j];
            cout << endl;
        }*/

        if(!R && !B)
            cout << "Case #" << cases++ << ": Neither" << endl;
        else if(R && !B)
            cout << "Case #" << cases++ << ": Red" << endl;
        else if(!R && B)
            cout << "Case #" << cases++ << ": Blue" << endl;
        else
            cout << "Case #" << cases++ << ": Both" << endl;
    }
    return 0;
}
