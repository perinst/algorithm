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

    unordered_map<int, vector<int>> map;

    for (vector<int> &edge : edges)
    {
        int node = edge[0];
        int next = edge[1];
        map[node].push_back(next);
        map[next].push_back(node);
    }

    int n = map.size();

    vector<int> listMaxTargetNodes;

    for (int i = 0; i < n; i++)
    {
        vector<bool> visited(n, false);

        queue<tuple<int, vector<int>, int>> q;

        visited[i] = true;

        q.push({k, map[i], 1});

        int maxTargetNode = 1;

        while (!q.empty())
        {
            auto [depth, nodes, currentTargetNodes] = q.front();
            q.pop();

            if (depth == 0)
            {
                maxTargetNode = max(maxTargetNode, currentTargetNodes);
                continue;
            }

            int nextSizeNode = 0;

            for (int &next : nodes)
            {

                if (!visited[next])
                {
                    nextSizeNode++;
                }
            }

            for (int &next : nodes)
            {

                if (!visited[next])
                {
                    visited[next] = true;
                    q.push({depth - 1, map[next], currentTargetNodes + nextSizeNode});
                }
            }
                }

        listMaxTargetNodes.push_back(maxTargetNode);
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
    vector<int> listMaxTargetNodeEdge2;

    if (k > 0)
    {
        listMaxTargetNodeEdge2 = maxNodeTargetEdge(edges2, k - 1);
    }

    vector<int> ans(listMaxTargetNodeEdge1.size());

    int maxTargetNodes = 0;

    if (k > 0)
    {

        for (int &targetNodes : listMaxTargetNodeEdge2)
        {
            maxTargetNodes = max(targetNodes, maxTargetNodes);
        }
    }

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

void solve()
{
    vector<vector<int>> edges1 = {{0, 1}};
    vector<vector<int>> edges2 = {{0, 1}};
    int k = 0;
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