#include <iostream>
#include <vector>
#include <queue>

#define vi vector<int>;
#define vii vector<vector<int>>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
using namespace std;

void addEdge(vii matrix, int i, int j)
{
    matrix[i][j] = 1;
    matrix[j][i] = 1;
}

void addEdgeAdj(vii &adj, int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
void bfs(vii &adj, int start, vector<bool> &visited)
{

    queue<int> q;

    visited[start] = true;

    q.push(start);

    while (!q.empty())
    {

        int edge = q.front();
        q.pop();
        cout << edge;

        for (int &e : adj[edge])
        {
            if (visited[e])
                continue;

            q.push(e);
            visited[e] = true;
        }
    }
}

int main()
{
    // Number of vertices in the graph
    int V = 5;
    //
    vector<vector<int>> adj(V);
    //
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    // bfs process
    vector<bool> visited(V, false);
    //
    bfs(adj, 0, visited);
    //
    return 0;
}