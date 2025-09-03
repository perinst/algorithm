#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u, v, w;
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {};
};
class DisjoinSetUnion
{
    vector<int> parent;
    vector<int> rank;

    DisjoinSetUnion(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] == find(parent[i]);
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

class Prim
{
};

class Kruskal
{
    int n, m;
    vector<Edge> edges;

    void input()
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
    }

    vector<Edge> kruskal()
    {

        std::sort(edges.begin, edges.end(), [](Edge &x, Edge &y)
                  { return x.w < y.w; });

        DisjoinSetUnion dsu(n);

        vector<Edge> minimumSpanningTree;
        long long mstWeight = 0;

        for (const Edge &edge : edges)
        {
            if (dsu.find(edge.u) != dsu.find(edge.v))
            {
                minimumSpanningTree.push_back(edge);
                mstWeight += edge.w;
                dsu.unite(edge.u, edge.v);
            }
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    while (T--)
    {
    }

    return 0;
}