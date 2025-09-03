#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
// const long long INF = 2000000000000000000LL;
struct Edge
{
    int u, v;
    long long w;
};

class BellmanFord
{
    void bellmanFord(int V, int E, const vector<Edge> &edges, int s)
    {
        vector<long long> dist(V, LLONG_MAX);
        dist[s] = 0;

        for (int T = 1; T < V - 1; T++)
        {
            for (const Edge &edge : edges)
            {
                int u = edge.u;
                int v = edge.v;
                long long w = edge.w;

                if (dist[u] != LLONG_MAX && dist[v] < dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        for (Edge &e : edges)
        {
            auto [u, v, w] = e;
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
            {
                std::cout << "Do thi chua chu trinh am!" << std::endl;
                exit(0);
            }
        }
    }
};

int main()
{
    return 0;
}