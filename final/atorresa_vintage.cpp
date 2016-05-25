#include <iostream>
#include <map>

using namespace std;

string undex("a quick brown fox jumps over the lazy dog.");

map<string, char> corresp;

void init()
{
    corresp[" oo  .  o"] = undex[0];
    corresp["  o  .   "] = undex[1];
    corresp[" ooo .  o"] = undex[2];
    corresp[" ooo .o o"] = undex[3];
    corresp[" oo o.  o"] = undex[4];
    corresp[" oo  . oo"] = undex[5];
    corresp[" oo o. oo"] = undex[6];
    corresp["  o  .   "] = undex[7];
    corresp[" oo  . o "] = undex[8];
    corresp[" ooo . o "] = undex[9];
    corresp[" oo o.ooo"] = undex[10];
    corresp[" ooo .ooo"] = undex[11];
    corresp[" oo o.oo "] = undex[12];
    corresp["  o  .   "] = undex[13];
    corresp[" oo  .oo "] = undex[14];
    corresp[" oo o.ooo"] = undex[15];
    corresp[" oooo.   "] = undex[16];
    corresp["  o  .   "] = undex[17];
    corresp[" oo o. o "] = undex[18];
    corresp[" ooo .o o"] = undex[19];
    corresp[" oo o.o o"] = undex[20];
    corresp[" ooo .   "] = undex[21];
    corresp[" ooo . oo"] = undex[22];
    corresp["  o  .   "] = undex[23];
    corresp[" oo o.ooo"] = undex[24];
    corresp[" ooo .oo "] = undex[25];
    corresp[" oo  .o o"] = undex[26];
    corresp[" ooo . o "] = undex[27];
    corresp["  o  .   "] = undex[28];
    corresp[" ooo .o  "] = undex[29];
    corresp[" oo o.   "] = undex[30];
    corresp[" oo  .o o"] = undex[31];
    corresp["  o  .   "] = undex[32];
    corresp[" oo o.o  "] = undex[33];
    corresp[" oo  .  o"] = undex[34];
    corresp[" oooo. o "] = undex[35];
    corresp[" oooo.  o"] = undex[36];
    corresp["  o  .   "] = undex[37];
    corresp[" oo  .o  "] = undex[38];
    corresp[" oo o.ooo"] = undex[39];
    corresp[" oo  .ooo"] = undex[40];
    corresp["  o o.oo "] = undex[41];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // WOuld have been more convenient to put the correspondance in the input directly
    init();

    string line;
    string undec("");
    while(getline(cin, line))
    {
        if(line[0] == '_') continue;

        line = line.substr(1, line.size() - 2);
        //cout << line << endl;
        undec += corresp[line];
    }
    cout << undec << endl;
    return 0;
}
