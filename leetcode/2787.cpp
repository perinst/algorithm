#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int numberOfWays(int n, int x)
{

    long long mod = 1e9 + 7;

    vector<long long> dp(n + 1);

    for (int num = 1; num <= n; num++)
    {
        long long val = pow(num, x);

        if (val > n)
            break;

        for (int j = n; j >= val; j--)
        {
            dp[j] = (dp[j] + dp[j - val]) % mod;
        }
    }

    return dp[n];
}

int numberOfWaysV2(int n, int x)
{

    long long mod = 1e9 + 7;

    vector<vector<long long>> dp(n + 1, vector<long long>(n + 1));

    dp[0][0] = 1;

    for (int num = 1; num <= n; num++)
    {
        long long val = pow(num, x);

        for (int j = 0; j <= n; j++)
        {
            dp[num][j] = dp[num - 1][j];
            if (val < n)
            {
                dp[num][j] = (dp[num][j] + dp[num - 1][j - val]) % mod;
            }
        }
    }

    return dp[n][n];
}

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
}

int main()
{

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}