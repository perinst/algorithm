#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < sz(v); i++)
    {
        os << v[i];
        if (i != sz(v) - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

int maxTargetNode(int node, int depth, unordered_map<int, vector<int>> &map)
{
    if (depth == 0)
        return 0;

    vector<int> nexts = map[node];

    int maxTarget = 1;

    for (int &nextNode : nexts)
    {
        maxTarget = nexts.size() + maxTargetNode(nextNode, depth - 1, map);
    }

    return maxTarget;
}

vector<int> maxNodeTargetEdge(vector<vector<int>> &edges, int k)
{
    int n = edges.size() + 1;

    if (k < 0)
        return vector<int>(n, 0);

    unordered_map<int, vector<int>> map;

    for (vector<int> &edge : edges)
    {
        int node = edge[0];
        int next = edge[1];
        map[node].push_back(next);
        map[next].push_back(node);
    }

    vector<int> listMaxTargetNodes(n, 0);

    for (int i = 0; i < n; i++)
    {
        vector<bool> visited(n, false);

        queue<pair<int, int>> q;

        q.push({k, i});
        visited[i] = true;

        int maxTargetNode = 1;

        while (!q.empty())
        {
            auto [depth, node] = q.front();
            q.pop();

            if (depth == 0)
            {
                continue;
            }

            int target = 0;

            for (int &next : map[node])
            {
                if (visited[next])
                    continue;

                target++;
                q.push({depth - 1, next});
                visited[next] = true;
            }

            maxTargetNode += target;
        }

        listMaxTargetNodes[i] = maxTargetNode;
    }

    return listMaxTargetNodes;
}

vector<int> maxTargetNodes1(vector<vector<int>> &edges1,
                            vector<vector<int>> &edges2, int k)
{
    const int n = edges1.size();
    const int m = edges2.size();

    unordered_map<int, int> freq_tre_1;

    vector<int> listMaxTargetNodeEdge1 = maxNodeTargetEdge(edges1, k);
    vector<int> listMaxTargetNodeEdge2 = maxNodeTargetEdge(edges2, k - 1);

    vector<int> ans(listMaxTargetNodeEdge1.size());

    int maxTargetNodes = *max_element(listMaxTargetNodeEdge2.begin(), listMaxTargetNodeEdge2.end());

    for (int i = 0; i < listMaxTargetNodeEdge1.size(); i++)
    {
        ans[i] = maxTargetNodes + listMaxTargetNodeEdge1[i];
    }

    return ans;
}

int dfs(int node, int root, vector<vector<int>> &child, int depth)
{

    if (depth < 0)
        return 0;

    int targetNodes = 1;

    for (int nextNode : child[node])
    {
        if (root == nextNode)
            continue;
        targetNodes += dfs(nextNode, node, child, depth - 1);
    }

    return targetNodes;
}

vector<int> build(vector<vector<int>> &edges, int k)
{

    int n = edges.size() + 1;
    vector<vector<int>> child(n);

    for (const auto &edge : edges)
    {
        child[edge[0]].push_back(edge[1]);
        child[edge[1]].push_back(edge[0]);
    }

    vector<int> listTargets(n);

    for (int i = 0; i < n; i++)
    {
        listTargets[i] = dfs(i, -1, child, k);
    }

    return listTargets;
}

vector<int> maxTargetNodes(vector<vector<int>> &edges1,
                           vector<vector<int>> &edges2, int k)
{
    const int n = edges1.size() + 1;
    const int m = edges2.size() + 1;

    vector<int> listTargetEdge1 = build(edges1, k);
    vector<int> listTargetEdge2 = build(edges2, k - 1);

    int maxTargetListEdge2 = *max_element(listTargetEdge2.begin(), listTargetEdge2.end());

    vector<int> ans(n);

    for (int i = 0; i < n; i++)
    {
        ans[i] = listTargetEdge1[i] + maxTargetListEdge2;
    }

    return ans;
}

class OptimizedSolution
{
private:
    // Single DFS with DP - O(n*k) instead of O(n²*k)
    vector<int> countNodesWithinK(vector<vector<int>> &edges, int k)
    {
        if (k < 0)
            return vector<int>(edges.size() + 1, 0);

        int n = edges.size() + 1;
        vector<vector<int>> adj(n);

        // Build adjacency list - O(n)
        for (auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<int> result(n);

        // DP: dp[d] = count of nodes at exactly distance d from current node
        function<vector<int>(int, int)> dfs = [&](int node, int parent) -> vector<int>
        {
            vector<int> dp(k + 1, 0);
            dp[0] = 1; // The node itself

            for (int child : adj[node])
            {
                if (child == parent)
                    continue;

                vector<int> child_dp = dfs(child, node);

                // Merge child results - add nodes at distance d+1
                for (int d = 0; d < k; d++)
                {
                    dp[d + 1] += child_dp[d];
                }
            }

            // Sum all distances <= k for this node
            result[node] = 0;
            for (int d = 0; d <= k; d++)
            {
                result[node] += dp[d];
            }

            return dp;
        };

        dfs(0, -1);
        return result;
    }

    // Re-rooting optimization for ultimate performance
    vector<int> rerootOptimization(vector<vector<int>> &edges, int k)
    {
        if (k < 0)
            return vector<int>(edges.size() + 1, 0);

        int n = edges.size() + 1;
        vector<vector<int>> adj(n);

        for (auto &edge : edges)
        {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // down[node][d] = count of nodes at distance d in subtree of node
        // up[node][d] = count of nodes at distance d outside subtree of node
        vector<vector<int>> down(n, vector<int>(k + 1, 0));
        vector<vector<int>> up(n, vector<int>(k + 1, 0));
        vector<int> result(n);

        // Phase 1: Compute downward DP (rooted at 0)
        function<void(int, int)> dfs1 = [&](int node, int parent)
        {
            down[node][0] = 1;

            for (int child : adj[node])
            {
                if (child == parent)
                    continue;

                dfs1(child, node);

                // Merge child's contribution
                for (int d = 0; d < k; d++)
                {
                    down[node][d + 1] += down[child][d];
                }
            }
        };

        // Phase 2: Compute upward DP and final answers
        function<void(int, int)> dfs2 = [&](int node, int parent)
        {
            // Calculate result for current node
            result[node] = 0;
            for (int d = 0; d <= k; d++)
            {
                result[node] += down[node][d] + up[node][d];
            }

            // Prepare upward DP for children
            vector<vector<int>> prefix(adj[node].size(), vector<int>(k + 1, 0));
            vector<vector<int>> suffix(adj[node].size(), vector<int>(k + 1, 0));

            int child_idx = 0;
            for (int child : adj[node])
            {
                if (child == parent)
                {
                    child_idx++;
                    continue;
                }

                // Copy downward contribution of this child
                for (int d = 0; d < k; d++)
                {
                    if (child_idx > 0)
                    {
                        prefix[child_idx][d + 1] = prefix[child_idx - 1][d + 1];
                    }
                    prefix[child_idx][d + 1] += down[child][d];
                }
                child_idx++;
            }

            // Build suffix arrays
            for (int i = adj[node].size() - 2; i >= 0; i--)
            {
                for (int d = 0; d <= k; d++)
                {
                    suffix[i][d] = suffix[i + 1][d] + prefix[i + 1][d];
                }
            }

            // Propagate to children
            child_idx = 0;
            for (int child : adj[node])
            {
                if (child == parent)
                {
                    child_idx++;
                    continue;
                }

                // Calculate upward contribution for this child
                for (int d = 0; d < k; d++)
                {
                    up[child][d + 1] = up[node][d] +
                                       (child_idx > 0 ? prefix[child_idx - 1][d + 1] : 0) +
                                       suffix[child_idx][d + 1];
                }
                up[child][0] = 1; // The parent node itself

                dfs2(child, node);
                child_idx++;
            }
        };

        dfs1(0, -1);
        dfs2(0, -1);

        return result;
    }

public:
    vector<int> maxTargetNodes(vector<vector<int>> &edges1,
                               vector<vector<int>> &edges2, int k)
    {
        // Use the optimized single-pass algorithm
        vector<int> tree1_counts = countNodesWithinK(edges1, k);
        vector<int> tree2_counts = countNodesWithinK(edges2, k - 1);

        // Find maximum in tree2
        int max_tree2 = 0;
        if (!tree2_counts.empty())
        {
            max_tree2 = *max_element(tree2_counts.begin(), tree2_counts.end());
        }

        // Combine results
        vector<int> result(tree1_counts.size());
        for (int i = 0; i < tree1_counts.size(); i++)
        {
            result[i] = tree1_counts[i] + max_tree2;
        }

        return result;
    }

    // For maximum performance, use re-rooting
    vector<int> maxTargetNodesUltraFast(vector<vector<int>> &edges1,
                                        vector<vector<int>> &edges2, int k)
    {
        vector<int> tree1_counts = rerootOptimization(edges1, k);
        vector<int> tree2_counts = rerootOptimization(edges2, k - 1);

        int max_tree2 = 0;
        if (!tree2_counts.empty())
        {
            max_tree2 = *max_element(tree2_counts.begin(), tree2_counts.end());
        }

        vector<int> result(tree1_counts.size());
        for (int i = 0; i < tree1_counts.size(); i++)
        {
            result[i] = tree1_counts[i] + max_tree2;
        }

        return result;
    }
};

void solve()
{
    vector<vector<int>> edges1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}};
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}};
    int k = 2;
    cout << maxTargetNodes1(edges1, edges2, k);
}

int main()
{
    fast_io;
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}