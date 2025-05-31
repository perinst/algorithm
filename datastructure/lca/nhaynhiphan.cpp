#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN]; // Adjacency list representation
int parent[MAXN];      // Parent array for path reconstruction

// Tìm đường đi từ u đến v bằng BFS
vector<int> findPath(int u, int v)
{
    queue<int> q;
    q.push(u);
    memset(parent, -1, sizeof(parent));
    parent[u] = u;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        if (node == v)
            break;

        for (int next : adj[node])
        {
            if (parent[next] == -1)
            {
                parent[next] = node;
                q.push(next);
            }
        }
    }

    vector<int> path;
    for (int cur = v; cur != u; cur = parent[cur])
    {
        path.push_back(cur);
    }

    path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
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

    int q;
    cin >> q;

    while (q--)
    {
        int u, v, k;
        cin >> u >> v >> k;
        vector<int> path = findPath(u, v);
        int steps = min(k, (int)path.size() - 1);
        cout << path[steps] << "\n";
    }

    return 0;
}
