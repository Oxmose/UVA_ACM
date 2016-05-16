#include <iostream>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    string line;
    while(cin >> line)
    {
        if(line == ".") break;

        string pattern("");
        size_t size = line.size();
        bool ok = false;
        for(unsigned int i = 0; i < size / 2; ++i)
        {
            pattern += line[i];
            if(size % pattern.size() != 0) continue; 

            string full("");
            while(full.size() != size)
                full += pattern;
            if(full == line)
            {
                cout << size / pattern.size() << endl;
                ok = true;
                break;
            }
        }
        if(!ok)
            cout << "1" << endl;
    }
	return 0;
}
