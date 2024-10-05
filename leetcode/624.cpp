#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

int maxDistance(vector<vector<int>> &arrays)
{
    int m = arrays.size();

    pair<int, int> minN = {-1, INT_MAX};
    pair<int, int> maxN = {-1, INT_MIN};

    for (int i = 0; i < m; i++)
    {
        if (minN.second > arrays[i][0])
        {
            minN = {i, arrays[i][0]};
        }
        if (maxN.second < arrays[i].back())
        {
            maxN = {i, arrays[i].back()};
        }
    }

    if (minN.first != maxN.first)
        return maxN.second - minN.second;

    int maxD = INT_MIN;
    int minD = INT_MAX;

    for (int i = 0; i < m; i++)
    {
        if (minN.first == i)
            continue;

        minD = min(minD, arrays[i][0]);
        maxD = max(maxD, arrays[i].back());
    }

    return max(maxD - minN.second, maxN.second - minD);
}

int main()
{

    return 0;
}