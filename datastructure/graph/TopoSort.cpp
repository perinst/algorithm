#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int maxN = 110;

int n, m;
int in_degree[maxN], ans[maxN];
vector<int> g[maxN], topo;
queue<int> listSource;

class TopoDFS
{
    int n, m;
    int visit[maxN], ans[maxN], dp[maxN];
    vector<int> g[maxN];
    stack<int> topo;
    vector<int> revTopo;

    void dfs(int u)
    {
        visit[u] = 1;

        for (auto v : g[u])
        {
            if (visit[u] == 1)
            {
                exit(0);
            }

            if (!visit[i])
                dfs(v);
        }
        topo.push(u);
        revTopo.push_back(u);
        visit[u] = 2;
    }

    int solve()
    {
        cin >> n >> m;

        while (m--)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }

        for (int i = 1; i <= n; i++)
        {
            if (!visit[i])
                dfs(i);
        }
        int ans = 0;

        for (auto u : revTopo)
        {
            for (auto v : g[u])
            {
                dp[u] = max(dp[u], dp[v] + 1);
            }
            ans = max(ans, dp[u]);
        }

        return 0;
    }
};

class ShortTestPathTopo
{

    int maxN = 1e10 + 5;
    int n, m, s;
    int visit[maxN], ans[maxN], dp[maxN];
    vector<vector<pair<int, int>>> adj;
    vector<int> g[maxN], topo, topoId;
    vector<long long> d;

    void dfs(int u)
    {
        this->visit[u] = 1;
        for (auto v : g[u])
        {
            if (!visit[v])
                dfs(v);
        }
        this->topo.push_back(u);
        this->visit[u] = 2;
    }

    int main()
    {
        cin >> n >> m >> s;

        while (m--)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }

        for (int i = 1; i <= n; i++)
        {
            if (!visit[i])
                dfs(i);
        }

        reverse(topo.begin(), topo.end());

        for (int i = 0; i < n; i++)
        {
            topoId[topo[i]] = i;
        }

        int ans = 0;
        fill(d.begin(), d.end(), INT_MAX);

        int index_s = topoId[s];

        for (int i = index_s; i < n; i++)
        {
            int u = topo[i];
            for (auto p : adj[u])
            {
                int v = p.first;
                int w = p.second;
                if (d[v] > d[u] + w)
                {
                    d[v] = d[u] + w;
                }
            }
        }
    }
};

int main()
{
    cin >> n >> m;
    while (m--)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        in_degree[v]++;
    }

    for (int u = 0; u < n; u++)
        if (!in_degree[u])
            listSource.push(u);

    while (!listSource.empty())
    {
        int u = listSource.front();
        listSource.pop();
        topo.push_back(u);

        for (auto v : g[u])
        {
            in_degree[v]--;
            if (in_degree[v] == 0)
            {
                listSource.push(v);
            }
        }
    }
}