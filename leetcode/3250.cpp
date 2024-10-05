#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;
const int mod = 1e9 + 7;
vector<int> nums;
vector<vector<int>> dp;

//  1 <= nums[i] <= 50 (!)


int recursion(int i, int s, int n)
{
    if (i == n)
        return 1;
    if (dp[i][s] != -1)
        return dp[i][s];

    int t = 0;
    for (int j = s; j <= nums[i]; j++)
    {
        if (i - 1 >= 0 && (nums[i] - j) <= (nums[i - 1] - s))
        {
            t += recursion(i + 1, j, n) % mod;
        }
        else if (i - 1 < 0)
        {
            t += recursion(i + 1, j, n) % mod;
        }
    }

    return dp[i][s] = t;
}

int countOfPairs(vector<int> &arr)
{

    nums = arr;
    int maximum = *max_element(nums.begin(), nums.end());
    int n = nums.size();

    dp.resize(n, vector<int>(maximum + 1, -1));
    // dp.resize(n, vector<int>(50,-1));

    return recursion(0, 0, n);
}

int main()
{

    return 0;
}