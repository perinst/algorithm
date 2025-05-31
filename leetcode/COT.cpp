#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node
{
    int sum;
    int left, right;
};

const int MAX_N = 100000;
const int MAX_LOG = 18;
int n, m;

vector<int> weight(MAX_N);
vector<vector<int>> adj(MAX_N);
// Binary lifting table
vector<vector<int>> up(MAX_N, vector<int>(MAX_LOG));
vector<vector<int>> values(MAX_N, vector<int>());
vector<int> depth(MAX_N);

void dfs(int u, int parent)
{
    for (int v : adj[u])
    {
        if (v == parent)
            continue;
        depth[v] = depth[u] + 1;
        up[v][0] = u;
        for (int i = 1; i < MAX_LOG; i++)
        {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        // Propagate the sorted values list
        values[v] = values[u];
        values[v].push_back(weight[u]);
        sort(values[v].begin(), values[v].end());
        dfs(v, u);
    }
}
// Function to find the LCA of u and v
int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);
    // Bring u and v to the same depth
    for (int i = MAX_LOG - 1; i >= 0; i--)
    {
        if (depth[u] - (1 << i) >= depth[v])
        {
            u = up[u][i];
        }
    }

    if (u == v)
        return u;

    for (int i = MAX_LOG - 1; i >= 0; i--)
    {
        if (up[u][i] != up[v][i])
        {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}
// Function to get the k-th smallest weight on the path from u to v
int get_kth_min_weight(int u, int v, int k)
{
    vector<int> path_values;
    while (depth[v] > depth[u])
    {
        path_values.push_back(weight[v]);
        v = up[v][0];
    }
    if (u == v)
    {
        path_values.push_back(weight[u]);
    }
    sort(path_values.begin(), path_values.end());
    // 0-based indexing, so we return k-1
    return path_values[k - 1];
}

int main()
{
    int N, M;
    cin >> N, M;
    vector<int> nodes(N);
    vector<vector<int>> uv(N - 1);

    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        // Converting to 0-based index
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Preprocess the tree using DFS and Binary Lifting
    depth[0] = 0; // Starting from node 0

    dfs(0, -1);

    while (m--)
    {
        int u, v, k;
        cin >> u >> v >> k;
        u--;
        v--; // Convert to 0-based index
        int lca_node = lca(u, v);
        cout << get_kth_min_weight(u, v, k) << endl;
    }

    return 0;
}
