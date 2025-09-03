#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
vector<long long> v;
vector<int> p;
vector<vector<int>> children;
vector<vector<long long>> dp;

void dfs(int node)
{

    if (children[node].empty())
    {
        dp[node][0] = 0;
        dp[node][1] = v[node];
        return;
    }

    for (int child : children[node])
    {
        dfs(child);
    }

    dp[node][0] = 0;
    for (int child : children[node])
    {

        dp[node][0] += max(dp[child][0], dp[child][1]);
    }

    bool canExclude = false;
    for (int child : children[node])
    {
        if (max(dp[child][0], dp[child][1]) == dp[child][1])
        {
            canExclude = true;
            break;
        }
    }

    if (!canExclude)
    {
        long long maxGain = LLONG_MIN;
        for (int child : children[node])
        {
            maxGain = max(maxGain, dp[child][1] - dp[child][0]);
        }
        dp[node][0] += maxGain;
    }

    dp[node][1] = v[node];
    for (int child : children[node])
    {
        dp[node][1] += dp[child][0];
    }
}
void solve(int root)
{
    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << "\n";
}

int main()
{
    fast_io;
    int T;

    cin >> T;

    while (T--)
    {
        int n;
        cin >> n;

        v.resize(n + 1);
        children.assign(n + 1, vector<int>());
        dp.assign(n + 1, vector<long long>(2, 0));

        for (int i = 1; i <= n; i++)
        {
            cin >> v[i];
        }

        int root = -1;
        for (int i = 1; i <= n; i++)
        {
            int parent;
            cin >> parent;
            // p[i] = parent;

            if (parent == 0)
            {
                root = i;
            }
            else
            {
                children[parent].push_back(i);
            }
        }
        solve(root);
    }

    return 0;
}