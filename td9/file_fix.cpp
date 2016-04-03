#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef struct directory directory;

struct directory
{
	string name;
	map<string, directory*> childs;
};

vector<string> split(string &str)
{
	vector<string> result;
	size_t pos = 0;

	while ((pos = str.find('/')) != string::npos)
	{
		if(!str.substr(0, pos).empty())
			result.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}

	if(!str.empty())
		result.push_back(str);
	return result;
}

void dfs(directory *dir, string cur)
{
	string next;
	if(dir->name.empty())
	{
		cout << "/" << endl;
		next = "";
	}
	else
	{
		next = cur + "/" + dir->name;
		cout << next << endl;
	}
	for(pair<string, directory*> entry : dir->childs)
	{
		dfs(entry.second, next);
	}
}

void create(directory *dir, int &cost, int step, const vector<string> &toCreate)
{
    if(step >= toCreate.size())
        return;
	if(dir->childs.find(toCreate[step]) == dir->childs.end())
	{
		directory *last = dir;
		for(; step < toCreate.size(); ++step)
		{
			directory *newDir = new directory;
			newDir->name = toCreate[step];
			last->childs.emplace(toCreate[step], newDir);
			last = newDir;
			++cost;
		}
	}
	else
	{
        create(dir->childs[toCreate[step]], cost, step + 1, toCreate);
	}
}

void clearAll(directory *dir)
{
	for(pair<string, directory*> entry : dir->childs)
	{
		clearAll(entry.second);
	}
	dir->childs.clear();
	delete dir;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    testCases = 1;
    int M, N;
    while(cin >> N)
    {

    	cin >> M;
    	directory *root = new directory;
    	root->name = "";

    	string dir;
    	for(; N > 0; --N)
    	{

    		cin >> dir;
    		vector<string> tree = split(dir);
    		directory *last = root;
    		for(string dirName : tree)
    		{
    			if(dirName.empty()) continue;
    			if(last->childs.find(dirName) != last->childs.end())
    			{
    				last = last->childs[dirName];
    			}
    			else
    			{
    				directory *newDir = new directory;
    				newDir->name = dirName;
    				last->childs.emplace(dirName, newDir);
    				last = newDir;
    			}
    		}
    	}


    	int cost = 0;
    	for(; M > 0; --M)
    	{
    		cin >> dir;
    		
    		vector<string> tree = split(dir);
			create(root, cost, 0, tree);
		
    	}

    	clearAll(root);
    	cout << "Case #" << testCases++ << ": " << cost << endl;
    }

    return 0;
} // main()
