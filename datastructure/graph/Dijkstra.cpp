#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree

// int minDistance(int dist[], int sptSet[])
// {
//     // Initialize min value
//     int min = INT_MAX, min_index;

//     for (int v = 0; v < 9; v++)
//     {
//         if (sptSet[v] == false && dist[v] <= min)
//         {
//             min = dist[v];
//             min_index = v;
//         }
//     }

//     return min_index;
// }

// A utility function to print the constructed distance
// array
// void printSolution(int dist[])
// {
//     cout << "Vertex \t Distance from Source" << endl;
//     for (int i = 0; i < 9; i++)
//         cout << i << " \t\t\t\t" << dist[i] << endl;
// }

// void dijkstra(int graph[V][V], int src)
// {

//     int dist[V]; // The output array.  dist[i] will hold the
//                  // shortest
//                  // distance from src to i;

//     int sptSet[V]; // sptSet[i] will be true if vertex i is
//                    // included in shortest
//                    // path tree or shortest distance from src to i is
//                    // finalized

//     // Initialize all distances as INFINITE and stpSet[] as
//     // false

//     for (int i = 0; i < V; i++)
//     {
//         dist[i] = INT_MAX;
//         sptSet[i] = false;
//     }

//     // Distance of source vertex from itself is always 0
//     dist[src] = 0;

//     for (int i = 0; i < 9- 1; i++)
//     {
//         // Pick the minimum distance vertex from the set of
//         // vertices not yet processed. u is always equal to
//         // src in the first iteration.

//         int u = minDistance(dist, sptSet);
//         // Mark the picked vertex as processed
//         sptSet[u] = true;

//         // Update dist value of the adjacent vertices of the
//         // picked vertex.
//         for (int v = 0; v < 9; v++)
//         {
//             if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
//             {
//                 dist[v] = dist[u] + graph[u][v];
//             }
//         }
//     }

//     printSolution(dist);
// }

class Dijkstra
{
public:
    void dijkstra(vector<vector<pii>> &graph, int src, int V)
    {
        std::vector<int> dist(V, INT_MAX);
        std::priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for (auto edge : graph[u])
            {
                int v = edge.first;
                int weight = edge.second;

                int weight_u_path = dist[u] + weight;
                int weight_v_path = dist[v];

                if (dist[u] != INT_MAX && weight_u_path < weight_v_path)
                {
                    dist[v] = weight_u_path;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Đỉnh \t Khoảng cách từ nguồn" << endl;
        for (int i = 0; i < V; i++)
        {
            if (dist[i] == INT_MAX)
                cout << i << " \t Không thể đến được" << endl;
            else
                cout << i << " \t " << dist[i] << endl;
        }
    }
};

int main()
{
    // int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
    //                    {4, 0, 8, 0, 0, 0, 0, 11, 0},
    //                    {0, 8, 0, 7, 0, 4, 0, 0, 2},
    //                    {0, 0, 7, 0, 9, 14, 0, 0, 0},
    //                    {0, 0, 0, 9, 0, 10, 0, 0, 0},
    //                    {0, 0, 4, 14, 10, 0, 2, 0, 0},
    //                    {0, 0, 0, 0, 0, 2, 0, 1, 6},
    //                    {8, 11, 0, 0, 0, 0, 1, 0, 7},
    //                    {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    // // Function call
    // dijkstra(graph, 0);

    int V = 6;

    vector<vector<pii>> graph(V);

    graph[0].push_back({1, 2});
    graph[0].push_back({2, 5});
    graph[0].push_back({4, 10});

    graph[1].push_back({0, 2});
    graph[1].push_back({2, 4});
    graph[1].push_back({3, 10});
    graph[1].push_back({4, 1});

    graph[2].push_back({0, 5});
    graph[2].push_back({1, 4});
    graph[2].push_back({3, 3});
    graph[2].push_back({4, 2});

    graph[3].push_back({1, 10});
    graph[3].push_back({2, 3});
    graph[3].push_back({4, 7});
    graph[3].push_back({5, 1});

    graph[4].push_back({0, 10});
    graph[4].push_back({1, 1});
    graph[4].push_back({2, 2});
    graph[4].push_back({3, 7});
    graph[4].push_back({5, 4});

    graph[5].push_back({3, 1});
    graph[5].push_back({4, 4});

    Dijkstra s;

    s.dijkstra(graph, 0, V);

    return 0;
}