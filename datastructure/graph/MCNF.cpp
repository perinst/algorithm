
/**
 * @file MCNF.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-06-12
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
Đề bài;

   Có một mạng giao thông được cấu thành từ các thành phố và các tuyến đường nối các thành phố đó.
   Mỗi tuyến đường được mô tả bằng 4 số nguyên:

      𝑢 : thành phố xuất phát,
      𝑣 : thành phố đến,
      𝑐: dung lượng (số xe tối đa có thể đi qua mỗi giờ),
      cost: chi phí để di chuyển một xe trên tuyến đường đó (ví dụ: phí cầu đường, nhiên liệu).

   Nhiệm vụ của bạn là tính toán số lượng xe tối đa có thể được vận chuyển từ thành phố A đến thành phố B trong một giờ,
   đồng thời đảm bảo rằng tổng chi phí để vận chuyển số xe đó là tối thiểu.

Yêu Cầu:
  Đầu vào:

       Dòng đầu tiên chứa hai số nguyên : M ,N  : số lượng thành phố và số lượng tuyến đường.

       Dòng tiếp theo, mỗi dòng chứa 4 số nguyên: 𝑢, 𝑣, 𝑐 và 𝑐𝑜𝑠𝑡 mô tả một tuyến đường có hướng từ 𝑢 đến 𝑣

       Dòng cuối cùng chứa hai số nguyên 𝐴 và 𝐵 : thành phố xuất phát và thành phố đích.

       Đầu ra: In ra hai số nguyên: Số lượng xe tối đa có thể vận chuyển từ 𝐴  đến 𝐵  và tổng chi phí.

Giá trị ràng buộc:

   1 ≤ 𝑁 ≤ 500
   1 ≤ 𝑀 ≤ 5000
   1 ≤ 𝑢 , 𝑣 ≤ 𝑁
   1 ≤ 𝑐 ≤ 10^6
   1 ≤ cost ≤ 10^6

*/

/**
 *  A => B : min cost and max cars amount
 *  Declare adjacency list of city for neighbors
 *  When start at city A , find maximum available cost and amount cars can pass through from city for each neighbor, recursion each when can get city B.
 *  maximum = min(cars, cars of neighbors).
 *
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge
{
    int to, rev, cap, cost;
};

class MinCostMaxFlow
{
private:
    vector<vector<Edge>> graph;
    vector<int> dist, parent, parent_edge;
    int n;

public:
    MinCostMaxFlow(int n) : n(n), graph(n), dist(n), parent(n), parent_edge(n) {}

    void addEdge(int from, int to, int cap, int cost)
    {
        graph[from].push_back({to, graph[to].size() - 1, cap, cost});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0, -cost}); // reverse edge
    }

    bool spfa(int source, int sink)
    {
        fill(dist.begin(), dist.end(), INT_MAX);
        vector<bool> inQueue(n, false);
        queue<int> q;

        dist[source] = 0;

        q.push(source);
        inQueue[source] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            inQueue[u] = false;

            for (int i = 0; i < graph[u].size(); i++)
            {
                Edge &edge = graph[u][i];

                if (edge.cap > 0 && dist[u] + edge.cost > dist[edge.to])
                {
                    q.push(edge.to);
                    dist[edge.to] = dist[u] + edge.cost;
                    parent[edge.to] = u;
                    parent_edge[edge.to] = i;

                    if (!inQueue[edge.to])
                    {
                        q.push(edge.to);
                        inQueue[edge.to] = true;
                    }
                }
            }
        }
        return dist[sink] != INT_MAX;
    }

    pair<int, long long> minCostMaxFlow(int &source, int &sink)
    {
        int maxFlow = 0;
        long long minCost = 0;

        while (spfa(source, sink))
        {
            // Find bottleneck capacity along the path
            int pathFlow = INT_MAX;

            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                int edgeIdx = parent_edge[v];
                pathFlow = min(pathFlow, graph[u][edgeIdx].cap);
            }

            // Update capacities and calculate cost
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                int edgeIdx = parent_edge[v];
                // Forward edge: decrease capacity
                graph[u][edgeIdx].cap -= pathFlow;
                // Reverse edge: increase capacity
                graph[v][graph[u][edgeIdx].rev].cap += pathFlow;
            }

            maxFlow += pathFlow;
            minCost += (long long)pathFlow * dist[sink];
        }
    }
};

int N, M;
int A, B;

// vector<vector<pair<int, pair<int, int>>>> adj;

// queue<int> q;

// // max heap
// priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<int>> pq;

// vector<bool> optimize;

// vector<pair<int, int>> path_cost;

// bool spfa()
// {

//     path_cost[A] = {0, 0};

//     pq.push({A, path_cost[A]});

//     optimize[A] = true;

//     while (!pq.empty())
//     {

//         auto [v, cost_info] = pq.top();

//         pq.pop();

//         for (pair<int, pair<int, int>> &neighbor : adj[v])
//         {
//             const int next_neighbor = neighbor.first;

//             if (v == B)
//             {
//                 path_cost[B] = min(path_cost[])
//             }
//             else
//             {
//                 const auto [c, cost] = neighbor.second;

//                 if (path_cost[v] < path_cost[u] + c)
//                 {

//                 }
//             }
//         }
//     }
// }

int main()
{
    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        int u, v, c, cost;
        cin >> u >> v >> c >> cost;
        adj[u].push_back({v, {c, cost}});
    }

    cin >> A >> B;
}