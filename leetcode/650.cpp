#include <iostream>
#include <vector>
#include <string>
using namespace std;

int len;

int dpHelper(int s, int lenCopy, vector<vector<int>> &dp)
{

    if (s == len)
        return 0;

    if (s > len)
        return 1000;

    if (dp[s][lenCopy] != -1)
        return dp[s][lenCopy];

    if (s == lenCopy)
        return dp[s][lenCopy] = 1 + dpHelper(s + lenCopy, lenCopy, dp);

    int copy = 1 + dpHelper(s, s, dp);

    int paste = 1 + dpHelper(s + lenCopy, lenCopy, dp);

    return dp[s][lenCopy] = min(copy, paste);
}

int minSteps(int n)
{
    if (n == 1)
        return 0;

    len = n;

    vector<vector<int>> dp(n, vector<int>(n, -1));

    return 1 + dpHelper(1, 1, dp);
}

int main()
{
    int n = 11;
    cout << minSteps(n);

    return 0;
}