#include <iostream>
#include <vector>

using namespace std;
int dp[501][501][3];
int m, n;

bool isValidNext(int &i, int &j) { return i < n && j < m; }

int dfs(vector<vector<int>> &coins, int i, int j, int neu)
{
    if (!isValidNext(i, j))
    {
        return INT_MIN;
    }

    if (dp[i][j][neu] != INT_MIN)
        return dp[i][j][neu];

    int steal = INT_MIN;
    int notSteal = INT_MIN;

    int down = dfs(coins, i + 1, j, neu);
    int right = dfs(coins, i, j + 1, neu);

    notSteal = coins[i][j] + max(down, right);

    if (coins[i][j] < 0 && neu > 0)
    {
        steal = max(dfs(coins, i + 1, j, neu - 1),
                    dfs(coins, i, j + 1, neu - 1));
    }

    return dp[i][j][neu] = max(steal, notSteal);
}

int maximumAmount(vector<vector<int>> &coins)
{
    m = coins.size();
    n = coins[0].size();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                dp[i][j][k] = INT_MIN;
            }
        }
    }

    return dfs(coins, 0, 0, 2);
}

int maximumAmount(vector<vector<int>> &coins)
{
    m = coins.size();
    n = coins[0].size();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                dp[i][j][k] = INT_MIN;
            }
        }
    }

    return dfs(coins, 0, 0, 2);
}

int main()
{
    return 0;
}