#include <iostream>
#include <vector>
#include <string>
using namespace std;

string removeDuplicate(string &s)
{
    string unique;

    int i = 0;

    while (i < s.size())
    {

        char currChar = s[i];
        unique += currChar;

        while (i < s.size() && s[i] == currChar)
        {
            i++;
        }
    }

    return unique;
}

int minimumHelper(string &s, int start, int end, vector<vector<int>> &dp)
{
    if (start > end)
        return 0;

    if (dp[start][end] != -1)
        return dp[start][end];

    int minTurn = 1 + minimumHelper(s, start + 1, end, dp);

    for (int k = start + 1; k <= end; k++)
    {
        if (s[k] != s[start])
            continue;

        int turnSplitMatch = minimumHelper(s, start, k - 1, dp) + minimumHelper(s, k + 1, end, dp);
        minTurn = min(turnSplitMatch, minTurn);
    }

    return dp[start][end] = minTurn;
}

int strangePrinter(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    return minimumHelper(s, 0, n - 1, dp);
}

int main()
{
    string s = "tbgtgb";

    cout << strangePrinter(s);

    return 0;
}