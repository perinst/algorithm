#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

char open = '(';
char close = ')';

void backtracking(string &currP, vector<string> &rs, int &n, int a_close,
                  int a_open)
{

    if (a_close > n || a_open > n)
        return;

    if (currP.size() == n * 2)
    {
        rs.push_back(currP);
    }

    if (a_close < n && a_close < a_open)
    {
        currP.push_back(close);
        backtracking(currP, rs, n, a_close + 1, a_open);
        currP.pop_back();
    }

    if (a_open < n)
    {
        currP.push_back(open);
        backtracking(currP, rs, n, a_close, a_open + 1);
        currP.pop_back();
    }
}

vector<string> generateParenthesis(int n)
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string currP = "(";
    vector<string> rs;
    vector<int, pair<char, string>> dp;

    backtracking(currP, rs, n, 0, 1);

    return rs;
}

int main()
{

    return 0;
}