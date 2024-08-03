#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

void maxLen(vector<int> &nums, vector<int> &sub, int start, int lis)
{
    if (start > nums.size())
    {
        lis = max(lis, sub.size());
        return;
    }
    if (sub.size() > lis)
    {
        list = sub.size();
    }

    for (int i = start; i < nums.size(); i++)
    {
        if (num[num.size() - 1] < nums[i])
        {
            sub.push_back(nums[i]);

            maxLen(nums, sub, i + 1, lis);

            sub.pop_back();
        }
    }
}

int lengthOfLIS(vector<int> &nums)
{

    int lis = INT_MIN;
    vector<int> sub;

    maxLen(nums, sub, 0, lis);

    return lis;
}

class SolutionLISDPMemo
{
public:
    int maxLen(vector<int> &nums, int start, vector<int> &dp)
    {

        if (dp[start] != -1)
        {
            return dp[start];
        }

        int max_length = 1;

        for (int i = start + 1; i < nums.size(); i++)
        {

            if (nums[i] > nums[start])
            {
                max_length = max(max_length, 1 + maxLen(nums, i, dp));
            }
        }

        return dp[start] = max_length;
    }

    int lengthOfLIS(vector<int> &nums)
    {

        int lis = 1;
        int n = nums.size();
        vector<int> dp(n, -1);

        for (int i = 0; i < n; i++)
        {
            lis = max(lis, maxLen(nums, i, dp));
        }
        return lis;
    }
};
int lengthOfLISDpTab(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    int lis = 1;
    int n = nums.size();
    vector<int> dp(n, 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[i] > nums[j])
            {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
            lis = max(lis, d[i]);
        }
    }
    return lis;
}

int main
{

    RudolfBuildKBridges s;

    s.cinInput();
    s.sovle();

    return 0;
}