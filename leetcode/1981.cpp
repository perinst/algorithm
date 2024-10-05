#include <iostream>
#include <vector>

using namespace std;

int n;
int m;
int target;

int solve(vector<vector<int>> &mat, int r)
{
}

int minimizeTheDifference(vector<vector<int>> &mat, int target)
{
    long long s = 0;
    n = mat.size();
    m = mat[0].size();

    vector<vector<long long>> dp(n, vector<long long>(m, -1));

    long long minDistance = 0;

    for (int c = 0; c < m; ++c)
    {
        minDistance =
            std::min(minDistance, solve(mat, target, c, 0, dp));
    }

    return minDistance;
}

int main()
{

    return 0;
}
