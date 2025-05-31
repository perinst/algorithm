// #include <iostream>
// #include <vector>

// using namespace std;

// const int MAXN = 100005;
// const int LOGN = 20; // Enough for n up to 10^6

// vector<int> adj[MAXN];
// int depth[MAXN];
// int parent[MAXN][LOGN]; // parent[u][i] is 2^i-th ancestor of u

// // Calculate depth and direct parent for each node
// void dfs(int u, int p)
// {
//     // Set direct parent
//     parent[u][0] = p;

//     // Process all neighbors
//     for (int v : adj[u])
//     {
//         if (v != p)
//         {
//             depth[v] = depth[u] + 1;
//             dfs(v, u);
//         }
//     }
// }

// // Precompute binary lifting table
// void preprocess(int n)
// {
//     // First initialize all entries to -1
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < LOGN; j++)
//         {
//             parent[i][j] = -1;
//         }
//     }

//     // Calculate depth and direct parents
//     depth[1] = 0; // assuming 1 is root
//     dfs(1, -1);

//     // Fill in ancestors
//     for (int j = 1; j < LOGN; j++)
//     {
//         for (int i = 1; i <= n; i++)
//         {
//             if (parent[i][j - 1] != -1)
//             {
//                 parent[i][j] = parent[parent[i][j - 1]][j - 1];
//             }
//         }
//     }
// }

// // Find LCA of two nodes
// int getLCA(int u, int v)
// {
//     // If v is deeper, swap them
//     if (depth[u] < depth[v])
//     {
//         swap(u, v);
//     }

//     // Bring u to same level as v
//     int diff = depth[u] - depth[v];
//     for (int i = 0; i < LOGN; i++)
//     {
//         if (diff & (1 << i))
//         {
//             u = parent[u][i];
//         }
//     }

//     // If v was ancestor of u
//     if (u == v)
//         return u;

//     // Move both up until just before LCA
//     for (int i = LOGN - 1; i >= 0; i--)
//     {
//         if (parent[u][i] != parent[v][i])
//         {
//             u = parent[u][i];
//             v = parent[v][i];
//         }
//     }

//     return parent[u][0];
// }

// // Get k-th node on path from u to v
// int getKthNode(int u, int v, int k)
// {
//     int lca = getLCA(u, v);
//     int distToLca = depth[u] - depth[lca];

//     // If k is in the path from u to LCA
//     if (k <= distToLca)
//     {
//         // Go up k steps from u
//         int curr = u;
//         for (int i = 0; i < LOGN; i++)
//         {
//             if (k & (1 << i))
//             {
//                 curr = parent[curr][i];
//             }
//         }
//         return curr;
//     }

//     // If k is in the path from LCA to v
//     int totalDist = distToLca + (depth[v] - depth[lca]);
//     if (k > totalDist)
//         return -1; // k is too large

//     // Need to go up from v by (totalDist - k) steps
//     k = depth[v] - depth[lca] - (k - distToLca);
//     int curr = v;
//     for (int i = 0; i < LOGN; i++)
//     {
//         if (k & (1 << i))
//         {
//             curr = parent[curr][i];
//         }
//     }
//     return curr;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     int n;
//     cin >> n;

//     // Read tree edges
//     for (int i = 0; i < n - 1; i++)
//     {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }

//     // Preprocess the tree
//     preprocess(n);

//     // Process queries
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int u, v, k;
//         cin >> u >> v >> k;
//         cout << getKthNode(u, v, k) << "\n";
//     }

//     return 0;
// }
#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 100005;
const int LOG = 20; // log2(MAXN) ~ 17 nên dùng 20 cho chắc chắn
vector<int> adj[MAXN];
int depth[MAXN];
int up[MAXN][LOG]; // up[v][j] là tổ tiên thứ 2^j của v

// DFS để tính depth và mảng nhảy nhị phân up[][]
void dfs(int node, int parent)
{
    up[node][0] = parent;
    for (int j = 1; j < LOG; j++)
    {
        if (up[node][j - 1] != -1)
            up[node][j] = up[up[node][j - 1]][j - 1];
        else
            up[node][j] = -1;
    }
    for (int next : adj[node])
    {
        if (next != parent)
        {
            depth[next] = depth[node] + 1;
            dfs(next, node);
        }
    }
}

// Tìm LCA của u và v
int getLCA(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v); // Đảm bảo u luôn sâu hơn hoặc bằng v

    // Đưa u lên cùng mức với v
    int diff = depth[u] - depth[v];
    for (int j = LOG - 1; j >= 0; j--)
    {
        if ((diff >> j) & 1)
        {
            u = up[u][j];
        }
    }

    if (u == v)
        return u; // Nếu v là tổ tiên của u

    // Nhảy nhị phân để tìm LCA
    for (int j = LOG - 1; j >= 0; j--)
    {
        if (up[u][j] != up[v][j])
        {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0]; // LCA là cha trực tiếp của u hoặc v
}

// Nhảy k bước từ u trên cây
int jump(int u, int k)
{
    for (int j = 0; j < LOG; j++)
    {
        if (k & (1 << j))
        {
            u = up[u][j];
            if (u == -1)
                break; // Nếu nhảy ra khỏi cây
        }
    }
    return u;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(up, -1, sizeof(up));
    depth[1] = 0;
    dfs(1, -1);

    int q;
    cin >> q;

    while (q--)
    {
        int u, v, k;
        cin >> u >> v >> k;

        int lca = getLCA(u, v);
        int dist = depth[u] + depth[v] - 2 * depth[lca];

        if (dist <= k)
        {
            cout << v << "\n";
        }
        else
        {
            int du = depth[u] - depth[lca];
            if (k <= du)
            {
                cout << jump(u, k) << "\n";
            }
            else
            {
                int dv = dist - k;
                cout << jump(v, dv) << "\n";
            }
        }
    }

    return 0;
}
