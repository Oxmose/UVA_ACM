#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    char cor[27];
    for(unsigned int i = 0; i < 26; ++i)
    {
        cor[i] = (char) ('A' + i);
    }
    cor[26] = ' ';

    map<string, bool> dico;

    string word;
    while(cin >> word)
    {
        if(word == "#") break;
        dico[word] = true;
    }

    string line;
    string text("");

    while(getline(cin, line))
    {
        text += line;
    }
    text = text.substr(0, text.size() - 1);

       
    int corKey[27];
    int count = 0;
    
    for(unsigned int m = 0; m < 27; ++m)
    {
        string dec(""); 
        map<char, int> uncor;
        for(unsigned int i = 0; i < 27; ++i)
        {
            uncor[cor[i]] = (i + m) % 27;
        }

        //for(auto i : uncor)
            //cout << i.first << " : " << i.second << endl;

        for(unsigned int i = 0; i < text.size(); ++i)
        {
            //cout << "R: " << text[i] << " U: " << uncor[text[i]] << " C: " << cor[uncor[text[i]]] << endl;
            if(text[i] != '\n')
                dec += cor[uncor[text[i]]];
            else
                dec += '\n';
        }

        //cout << dec << endl;

        count = 0;
        stringstream ss(dec);
        string word;
        while(ss >> word)
            if(dico.find(word) != dico.end())
                ++count;

        corKey[m] = count;
    }

    int max = 0;
    int key;
    for(unsigned int i = 0; i < 27; ++i)
        if(max < corKey[i])
        {
            max = corKey[i];
            key = i;
        }

    string dec(""); 
    map<char, int> uncor;
    for(unsigned int i = 0; i < 27; ++i)
    {
        uncor[cor[i]] = (i + key) % 27;
    }

    for(unsigned int i = 0; i < text.size(); ++i)
    {
        if(text[i] != '\n')
            dec += cor[uncor[text[i]]];
        else
            dec += '\n';
    }

    int toRead = dec.size();
    stringstream sst(dec);
    string snd("");
    string buff("");
    while(toRead > 0)
    {
        if(snd.size() != 0)
            buff += snd + " ";
        while(sst >> snd && buff.size() + snd.size() <= 60)
        {
            buff += snd + " ";            
        }

        toRead -= buff.size() + 1;
        cout << buff.substr(0, buff.size() - 1) << endl;
        buff = "";        
    }
    //cout << dec << endl;

    return 0;
}
