#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<int> dp(n + 1, triangle.front());

    for (int r = 0; r < n - 1; r++)
    {
        for (int c = 0; c <= r; c++)
        {
            dp[c] = triangle[r][c] + min(dp[c], dp[c + 1]);
        }
    }

    return dp[n];
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

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}