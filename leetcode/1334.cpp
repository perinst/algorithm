#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int threshold;

int bfs(std::unordered_map<int, vector<pair<int, int>>> &map, vector<int> &dp, int from, int currDistance)
{

    if (currDistance > threshold || dp[from] != -1)
    {
        return 0;
    }

    dp[from] = 1;

    int count = 1;
    cout << "from " << from << " to: ";

    for (auto &edge : map[from])
    {
        int to = edge.first;
        int w = edge.second;

        if (currDistance + w <= threshold)
        {
            cout << to << "\t";
            count += bfs(map, dp, to, currDistance + w);
        }
    }

    cout << endl;

    return count;
}

int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
{

    std::unordered_map<int, vector<pair<int, int>>> map;

    threshold = distanceThreshold;

    for (const auto &edge : edges)
    {
        int from = edge[0];
        int to = edge[1];
        int w = edge[2];

        map[from].push_back({to, w});
        map[to].push_back({from, w});
    }

    int minAmountEdge = -1;
    int minA = INT_MAX;

    for (int i = 0; i < n; ++i)
    {
        vector<int> dp(n, -1);
        int amount = bfs(map, dp, i, 0) - 1;
        cout << endl;
        cout << i << ": " << amount << endl;
        if (amount < minA)
        {
            minAmountEdge = i;
            minA = amount;
        }
        else if (amount == minA)
        {
            minAmountEdge = max(i, minAmountEdge);
        }
    }
    return minAmountEdge;
}
class Solution
{
public:
    int threshold;

    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {

        std::vector<vector<pair<int, int>>> adjacencyList(n);
        std::vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INT_MAX));

        threshold = distanceThreshold;

        for (const auto &edge : edges)
        {
            int from = edge[0];
            int to = edge[1];
            int w = edge[2];

            adjacencyList[from].push_back({to, w});
            adjacencyList[to].push_back({from, w});
        }

        int minAmountEdge = -1;
        int minA = INT_MAX;

        for (int i = 0; i < n; ++i)
        {
            vector<int> dp(n, -1);

            int amount = bfs(adjacencyList, dp, i, 0) - 1;

            cout << endl;
            cout << i << ": " << amount << endl;
            if (amount < minA)
            {
                minAmountEdge = i;
                minA = amount;
            }
            else if (amount == minA)
            {
                minAmountEdge = max(i, minAmountEdge);
            }
        }
        return minAmountEdge;
    }

} int main()
{
    int n = 6;
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 2, 1},
        {2, 3, 1},
        {1, 3, 1},
        {1, 4, 1},
        {4, 5, 10}};

    int distanceThreshold = 20;

    cout << findTheCity(n, edges, distanceThreshold) << endl;

    return 0;
}