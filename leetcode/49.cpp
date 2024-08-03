#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

int solve()
{
}

vector<vector<string>> groupAnagrams(vector<string> &strs)
{

    std::unordered_map<string, vector<std::string>> mapStr;
    vector<vector<string>> ans;

    for (auto &str : strs)
    {
        string temp = str;
        std::sort(temp.begin(), temp.end());
        mapStr[temp].push_back(str);
    }

    for (auto &pair : mapStr)
    {
        ans.push_back(pair.second);
    }

    return ans;
}

int main()
{

    return 0;
}