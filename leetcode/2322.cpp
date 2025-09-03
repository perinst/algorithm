#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

int calc(int part1, int part2, int part3)
{
    return max(part1, max(part2, part3)) - min(part1, min(part2, part3));
}

void dfs(int node, vector<bool> &visited, vector<vector<int>> &adj, vector<int> &nums, int &xorValue)
{

    visited[node] = true;
    xorValue ^= nums[node];

    for (int &neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, visited, adj, nums, xorValue);
        }
    }
}

vector<int> getComponentXors(vector<int> &nums, vector<vector<int>> &edges,
                             int skipEdge1, int skipEdge2)
{

    int n = nums.size();
    vector<vector<int>> adj(n);

    for (int i = 0; i < edges.size(); i++)
    {
        if (i == skipEdge1 || i == skipEdge2)
            continue;
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> visited(n, false);
    vector<int> componentXors;

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
            continue;

        int xorValue = 0;

        dfs(i, visited, adj, nums, xorValue);

        componentXors.push_back(xorValue);
    }

    return componentXors;
}

int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
{
    int n = nums.size();
    int eSize = edges.size();
    vector<vector<int>> adj;
    int minScore = INT_MAX;

    for (int i = 0; i < eSize; i++)
    {
        for (int j = i + 1; j < eSize; j++)
        {
            // Chose pair edge to remove
            int skipIndexEdge1 = i;
            int skipIndexEdge2 = j;

            vector<int> xors = getComponentXors(nums, edges, skipIndexEdge1, skipIndexEdge2);

            if (xors.size() == 3)
            {

                std::sort(xors.begin(), xors.end());
                int score = xors[2] - xors[0];
                minScore = min(minScore, score);
            }
        }
    }

    return minScore;
};

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    vector<vector<int>> edges;

    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    for (int i = 0; i < N - 1; i++)
    {
        cin >> edges[i][0] >> edges[i][1];
    }

    cout << minimumScore(nums, edges) << endl;
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}