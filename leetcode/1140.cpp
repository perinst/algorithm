#include <iostream>
#include <vector>
#include <string>
// Overload the << operator for vector<int>
std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
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
int n;

int maxStones(vector<int> &suffixSum, int m, int currIndex, vector<vector<int>> &memo)
{
    if (currIndex + 2 * m > n)
        return suffixSum[currIndex];

    if (memo[currIndex][m] > 0)
        return memo[currIndex][m];

    int res = INT_MAX;

    for (int i = 1; i <= 2 * m; i++)
    {
        res = min(res, maxStones(suffixSum, max(i, m), currIndex + i, memo));
    }

    memo[currIndex][m] = suffixSum[currIndex] - res;

    return memo[currIndex][m];
}

int stoneGameII(vector<int> &piles)
{

    n = piles.size();
    vector<vector<int>> memo(piles.size(), vector<int>(piles.size()));

    vector<int> suffixSum = piles;

    for (int i = n - 2; i >= 0; i--)
    {
        suffixSum[i] += suffixSum[i + 1];
    }

    return maxStones(suffixSum, 1, 0, memo);
}
int main()
{
    vector<int> piles = {2, 7, 9, 4, 4};
    stoneGameII(piles);
    return 0;
}