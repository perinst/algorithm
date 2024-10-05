#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> paths;

void bfs(vector<pair<int, int>> &graph, int &source, int &destination, int target)
{
}

vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> edges, int source, int destination, int target)
{

    // vector<tuple<int, int, int>> graph(n);
    vector<pair<int, int>> graph(n);

    for (int i = 0; edges.size(); i++)
    {
        int from = edges[i][0];
        int to = edges[i][1];
        int w = edges[i][2];

        graph[from] = {to, w};
    }
}

int main()
{

    return 0;
}