#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

/*
Alice and Bob like to play a game using trees. Let there be a tree with n nodes that are labeled from 1 to n. Let p[i] be the parent of node i, and let p[i] = 0 if node i is the root. Lastly, let v[i] be the integer value of node i assigned to it.


For instance, the tree above describes the case where n = 6, v = [30, 15, 10, 20, 15, 18] and p = [0, 1, 1, 3, 3, 3]. The number next to each node is the integer value assigned to it. In this tree, p[1] = 0 indicates that node 1 is the root node. Notice that every node except for the root node has a parent node.

If a node-subset S of the tree satisfies the following conditions, then we call it a "good node-subset":

Condition 1: If x is in S, then child/parent node(s) of x (that are connected to x) are NOT in S.
Condition 2: If x with 1 or more child node(s) is NOT in S, then at least one child node of x is in S.
In the tree above, consider the following node-subsets:

S = {}: Condition 2 is not satisfied -- Node 3 is not in S, and thus at least one of {4, 5, 6} must be in S. Hence it is not a good node-subset.
S = {3}: This is a good node-subset as it satisfies both conditions.
S = {1, 2, 3}: Condition 2 is satisfied, but condition 1 is not.
S = {1, 4, 6}: This is a good node-subset as it satisfies both conditions.
S = {2, 3}: This is a good node-subset as it satisfies both conditions.
Let Score(S) be the score of a good node-subset S where it is the sum of the values assigned to the nodes in S. In the above example, if S = {1, 4, 5, 6}, then Score(S) = 30 + 20 + 15 + 18 = 83, which is the highest score achievable.

Given a tree, compute the largest score of a good node-subset that Alice and Bob can achieve.

Input
The first line of the input will contain T, the number of test cases.

The first line of each test case will contain n, the number of nodes. The second line will contain n integers separated by whitespace, describing the values assigned to nodes (v[1], ..., v[n]). The third line will contain n integers separated by whitespace, describing the parent of each node (p[1], ..., p[n]).

Output
Output the answer for each test case in each line.

Limit
1 ≤ T ≤ 10
2 ≤ n ≤ 100,000
-109 ≤ v[i] ≤ 109 (i = 1, 2, ..., n)
0 ≤ p[i] ≤ n (i = 1, 2, ..., n)
For each test case:
Among i = 1, 2, ..., n, p[i] = 0 holds for exactly one i.
For all i, p[i] ≠ i.
*/

using namespace std;
const int MOD = 1e9 + 7;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Solution
{
public:
    int N;
    vector<int> p;
    vector<long long> v;
    vector<vector<long long>> dp;
    vector<vector<int>> childs;

    long long max_score;

    void input()
    {
        cin >> N;
        v.resize(N);
        p.resize(N);
        childs.assign(N + 1, vector<int>());
        dp.assign(N + 1, vector<long long>(2, 0));

        for (size_t i = 0; i < N; i++)
        {
            cin >> v[i];
        }

        for (size_t i = 1; i < N; i++)
        {
            int parent;
            cin >> parent;
            p[i] = parent;
            childs[parent].push_back(i);
        }
    }

    void dfs(int node)
    {
        if (childs[node].empty())
        {
            dp[node][0] = 0;
            dp[node][1] = v[node];
            return;
        }

        for (int child : childs[node])
        {
            dfs(child);
        }

        //.
        dp[node][0] = 0;
        for (int child : childs[node])
        {
            dp[node][0] += max(dp[child][0], dp[child][1]);
        }

        //..
        bool canExclude = false;

        for (int child : childs[node])
        {
            if (max(dp[child][0], dp[child][1]) == dp[child][1])
            {
                canExclude = true;
                break;
            }
        }
        //????
        if (!canExclude)
        {
            long long maxGain = LONG_LONG_MAX;
            for (int child : childs[node])
            {
                maxGain = max(maxGain, dp[child][1] - dp[child][0]);
            }
            dp[node][0] += maxGain;
        }
        //!!!!
        dp[node][1] = v[node];
        for (int child : childs[node])
        {
            dp[node][1] += dp[child][0];
        }
    }

    void solve()
    {
        input();
        int root = 0;
        dfs(root);
        cout << max(dp[root][0], dp[root][1]) << endl;
    }
};

int main()
{
    fast_io;

    int T = 1;
    cin >> T;

    while (T--)
    {
        Solution s;
        s.solve();
    }

    return 0;
}