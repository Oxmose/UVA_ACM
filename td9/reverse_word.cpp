#include<iostream>
#include<stack>
#include<sstream>

using namespace std;

int main()
{
    int cases;
    cin >> cases;
    cin.ignore();
    string line;
    int id = 1;
    while(getline(cin, line))
    {
        stack<string> st;
        stringstream ss(line);
        string word;
        while(ss >> word)
        {
            st.push(word);
        }
        cout << "Case #" << id << ": ";
        while(!st.empty())
        {
            cout << st.top();
            if(st.size() != 1)
                cout << " ";
            st.pop();
        }
        cout << endl;
        ++id;
    }
    return 0;
}
