#include <iostream>	//std::cout
#include <string>	//std::string
#include <sstream>	//std::string
#include <map>		//std::map
#include <vector>	//std::vector
#include <set>		//std::set

using namespace std;

unsigned int count(const vector<unsigned int> &vect, unsigned int value)
{
    unsigned int count = 0;

    for(unsigned int i : vect)
        if(i == value)
            ++count;

    return count;
} // count(const vecotr<u_int>&, u_int)

int main()
{
    string line;
    while(getline(cin, line))
    {
        // Get the number of review by paper and of paper to review
        stringstream 	splitter(line);
        unsigned short 	reviewCount;
        unsigned int	papersCount;

        splitter >> reviewCount >> papersCount;

        // Continue on case K = N = 0
        if(reviewCount == papersCount && papersCount == 0) return 0;

        // Map contains paper id as key and name of the institution as value
        map<unsigned int, string> paperByInst;

        // Map contains paperId as key, count of review as first element in
        // pair and reviewers's ID as second element of pair
        map<unsigned int, pair<unsigned int, vector<unsigned int>>> paperMap;

        // Browse the reviewers
        for(unsigned int i = 0; i < papersCount; ++i)
        {
            getline(cin, line);
            stringstream reviewerSplitter(line);

            // Let's retrieve reviewer institution name
            string institution;
            reviewerSplitter >> institution;

            // Load data into containers
            paperByInst.emplace(i, institution);
            vector<unsigned int> papers;

            // Check the reviewed papers
            for(unsigned int j = 0; j < reviewCount; ++j)
            {
                unsigned int paperId;
                reviewerSplitter >> paperId;
                --paperId;

                if(paperMap.find(paperId) == paperMap.end())
                {
                    vector<unsigned int> revs;
                    revs.push_back(i);
                    pair<unsigned int, vector<unsigned int>> tuple = make_pair(1, revs);
                    paperMap.emplace(paperId, tuple);
                }
                else
                {
                    ++paperMap.at(paperId).first;
                    paperMap.at(paperId).second.push_back(i);
                }
            }
        }

        // Process data
        unsigned int errors = 0;
        for(unsigned int i = 0; i < papersCount; ++i)
        {
            if(paperMap.find(i) == paperMap.end())
            {
                ++errors;
                continue;
            }

            pair<unsigned int, vector<unsigned int>> paper = paperMap.at(i);

            //check if paper has the right amount of reviews
            if(paper.first != reviewCount)
            {
                ++errors;
                continue;
            }

            // check if was not reviewed
            // multiple times byt the same reviewer
            for(unsigned int j = 0; j < reviewCount; ++j)
            {
                if(paperByInst.find(i) == paperByInst.end() || paperByInst.at(i) == paperByInst.at(paper.second[j]) || count(paper.second, paper.second[j]) != 1)
                {
                    ++errors;
                    break;
                }
            }
        }

        if(errors)
                cout << errors << " PROBLEMS FOUND" << endl;
        else
                cout << "NO PROBLEMS FOUND" << endl;
    }
    return 0;
} // main()
