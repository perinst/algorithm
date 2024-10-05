#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<int, pair<vector<int>, vector<double>>> map;
int end_val;

double findProbability(int node, vector<int> &dp)
{

    if (node == end_val)
        return 0;

    if (dp[node] != -1)
        return dp[node];

    pair<vector<int>, vector<double>> e = map[node];

    int maxP = 0;

    for (int i = 0; i < e.first.size(); i++)
    {
        int p = e.second[i] * findProbability(e.first[i], dp);
        maxP = max(maxP, p);
    }

    return dp[node] = max(dp[node], maxP);
}

double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
{

    queue<pair<int, int>> q;
    vector<int> dp(n, -1);
    end_val = end_node;

    for (int i = 0; i < n; i++)
    {
        int from = edges[i][0];
        int to = edges[i][1];

        pair<vector<int>, vector<double>> e = map[from];

        e.first.push_back(to);
        e.second.push_back(succProb[i]);
    }

    return findProbability(start_node, dp);
}

int main()
{
    int n = 3;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
    vector<double> succProb = {0.5, 0.5, 0.2};
    int start = 0, end = 2;
    cout << maxProbability(n, edges, succProb, start, end);
    return 0;
}