#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <string>

using namespace std;

vector<char> changedDic;
vector<int> costDic;
unordered_map<char, vector<int>> mapChange;

int minCostCharacter(vector<int> idxCost, char &c_target, vector<bool> &memo)
{

    int minCost = INT_MAX;

    for (int i : idxCost)
    {
        if (memo[i] || c_target == changedDic[i])
            return 0;

        memo[i] = true;

        int minC = costDic[i] + minCostCharacter(mapChange[changedDic[i]], c_target, memo);

        if (minC < minCost)
        {
            minCost = minC;
        }
    }

    return minCost;
}

long long minimumCost(string source, string target, vector<char> &original, vector<char> &changed, vector<int> &cost)
{
    int n = source.size();

    changedDic = changed;
    costDic = cost;

    int totalMinCost = 0;

    for (int i = 0; i < original.size(); i++)
    {
        mapChange[original[i]].push_back(i);
    }

    for (int i = 0; i < n; i++)
    {

        if (source[i] == target[i])
            continue;

        char c_source = source[i];
        char c_target = target[i];

        std::vector<bool> memo(cost.size(), false);

        int minCostPerC = minCostCharacter(mapChange[c_source], c_target, memo);

        if (minCostPerC == 0 || minCostPerC == INT_MAX)
            return -1;
        totalMinCost += minCostPerC;
    }
    return totalMinCost;
}
int main()
{

    return 0;
}