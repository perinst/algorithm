#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;
class Solution
{
public:
    // bool solve(string &pattern, string &s)
    // {
    //     unordered_map<string, string> mp;
    //     int d = 0;
    //     string t = "";
    //     for (int i = 0; i < s.size(); i++)
    //     {

    //         if (!isspace(s[i]))
    //         {
    //             t += s[i];
    //             continue;
    //         }

    //         if (mp.empty())
    //         {
    //             mp[t] = pattern[d];
    //         }
    //         else if (mp.count(t) && mp[t] != s[d])
    //             return false;

    //         d++;
    //         t = "";
    //     }
    //     return true;
    // }
    bool solvev2(string &pattern, string &s)
    {

        unordered_map<char, string> pToS;
        unordered_map<string, char> sToP;

        vector<string> words;
        stringstream ss(s);
        string word;

        while (ss >> word)
        {
            words.push_back(word);
        }

        if (pattern.size() != words.size())
            return false;

        for (int i = 0; i < words.size(); i++)
        {
            char p = pattern[i];
            string w = words[i];

            if (pToS.count(p) && pToS[p] != w)
                return false;
            if (sToP.count(w) && sToP[w] != p)
                return false;

            pToS[p] = w;
            sToP[w] = p;
        }
        return true;
    }
};

int main()
{
    Solution solution;
    string pattern = "abbc";
    string s = "dog cat cat dog";
    cout << solution.solvev2(pattern, s) << endl;
    return 0;
}