#include <iostream>
#include <map>
#include <sstream>

using namespace std;

int main()
{
	string line;
	map<string, string> dico;
	while(getline(cin, line))
	{
		if(line.empty())
			break;
		string word, value;
		stringstream ss(line);
		ss >> value >> word;
		dico.emplace(word, value);
	}
	string word; 

	while(cin >> word)
	{
		if(dico.find(word) == dico.end())
			cout << "eh" << endl;
		else
			cout << dico[word] << endl;
	}
	return 0;
}
