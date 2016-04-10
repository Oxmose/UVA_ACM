#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef struct letter letter;
struct letter
{
    char character;
    vector<letter*> next;
};

map<string, bool> words;
int found = 0;

void dfs(letter *let, string cur = "", int step = -1)
{
    if(let->character != '.')
    {
        cur += let->character;
        bool founds = false;
        for(pair<string, bool> word : words)
        {
            //cout << "L : " << word.first[step] << " CHAR : " << let->character << endl;
            if(word.first[step] == let->character)
            {
                founds = true;
                break;
            }
        }
        if(!founds)
            return;
    }
    if(let->next.empty())
    {
        
        if(words.find(cur) != words.end())
        {
           
            ++found;
        }
    }
    else
        for(letter *next : let->next)
            dfs(next, cur, step + 1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, D, N;
    cin >> L >> D >> N;
    for(int i = 0; i < D; ++i)
    {
        string word;
        cin >> word;
        words.emplace(word, true);
    }

    int caseId = 1;
    
    for(int i = 0; i < N; ++i)
    {
        string word;
        cin >> word;
                
        letter *root = new letter;
        root->character = '.';
        
        vector<letter*> lasts;
        lasts.push_back(root);

        vector<letter*> nextC;

        bool par = false;
        for(unsigned int j = 0; j < word.size(); ++j)
        {
            if(word[j] == '(')
                par = true;
            else if(word[j] == ')')
            {
                for(letter* let : lasts)
                    let->next = nextC;
                lasts = nextC;
                nextC.clear();
                par = false;
            }
            else if(!par)
            {
                letter *let = new letter;
                let->character = word[j];

                for(letter *last : lasts)
                    last->next.push_back(let);
                lasts.clear();
                lasts.push_back(let);
            }
            else
            {
                letter *let = new letter;
                let->character = word[j];
                nextC.push_back(let);
            }
        }

        dfs(root);
        cout << "Case #" << caseId++ << ": " << found << endl;
        found = 0;
    }

    return 0;
}
