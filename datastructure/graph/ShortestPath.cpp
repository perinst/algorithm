#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits>

using namespace std;

class ShortestPathBruteForce
{
    unordered_map<int, vector<pair<int, int>>> graph;
    int minCost;

private:
    void findShortestPath(int current, int &destination, unordered_set<int> &path, int cost)
    {
        if (current == destination)
        {
            minCost = min(minCost, cost);
            return;
        }

        for (const auto &neighbor : graph[current])
        {
            int nextVertex = neighbor.first;
            int weight = neighbor.second;

            if (path.find(nextVertex) == path.end())
            {
                path.insert(nextVertex);
                findShortestPath(nextVertex, destination, path, cost + weight);
                path.erase(nextVertex);
            }
        }
    }

public:
    ShortestPathBruteForce(unordered_map<int, vector<pair<int, int>>> g) : graph(g), minCost(numeric_limits<int>::max()) {}
    int getShortestPath(int start, int destination)
    {
        unordered_set<int> path;
        path.insert(start);
        findShortestPath(start, destination, path, 0);
        return (minCost == numeric_limits<int>::max()) ? -1 : minCost;
    }
};

class findShortestMemo
{
    std::unordered_map<int, pair<int, int>> memo;

    void findShortestPath(int &current, int &destination)
    {
    }
}

void
test()
{
    vector<pair<unordered_map<int, vector<pair<int, int>>>, pair<int, int>>> testCases = {
        // Test 1: Đồ thị đơn giản, đường đi duy nhất
        {{{0, {{1, 4}}}, {1, {{2, 3}}}, {2, {}}},
         {0, 2}},

        // Test 2: Đồ thị có nhiều đường đi
        {{{0, {{1, 2}, {2, 5}}}, {1, {{2, 1}, {3, 6}}}, {2, {{3, 2}}}, {3, {}}},
         {0, 3}},

        // Test 3: Đồ thị có vòng nhưng không ảnh hưởng đường đi ngắn nhất
        {{{0, {{1, 2}, {2, 5}}}, {1, {{2, 1}, {3, 6}}}, {2, {{3, 2}, {0, 10}}}, {3, {}}},
         {0, 3}},

        // Test 4: Không có đường đi từ start đến destination
        {{{0, {{1, 3}}}, {1, {{2, 2}}}, {2, {}}}, {0, 5}},

        // Test 5: Đồ thị chỉ có một đỉnh
        {{{0, {}}}, {0, 0}}};

    for (size_t i = 0; i < testCases.size(); i++)
    {
        ShortestPathBruteForce solver(testCases[i].first);
        auto &[start, end] = testCases[i].second;
        int result = solver.getShortestPath(start, end);
        cout << "Test " << i + 1 << ": " << (result == -1 ? "No Path" : to_string(result)) << endl;
    }
}

int main()
{
    test();
    return 0;
}