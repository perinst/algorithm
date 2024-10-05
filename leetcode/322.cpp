
#include <iostream>
#include <vector>
#include <algorithm>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

using namespace std;

int n;

int dpHelper(vector<int> &coins, int remain, int idx, vector<vector<int>> &dp)
{
    if (remain <= 0)
        return 0;

    if (dp[idx][remain] != -1)
        return dp[idx][remain];
    int take = INT_MAX;

    if (remain >= coins[idx])
    {
        take = 1 + dpHelper(coins, remain - coins[idx], idx, dp);
    }

    int notTake = dpHelper(coins, remain, idx - 1, dp);

    return dp[idx][remain] = min(take, notTake);
}

int coinChange(vector<int> &coins, int amount)
{

    n = coins.size();

    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));

    return dpHelper(coins, amount, n - 1, dp);
}

int main()
{
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    cout << coinChange(coins, amount);
    return 0;
}