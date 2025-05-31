#include <iostream>
#include <vector>
#include <string>

using namespace std;

int maxAbsoluteSum(vector<int> &nums)
{
    int n = nums.size();
    int minPrefixSum = INT_MAX, maxPrefixSum = INT_MIN;
    int prefixSum = 0, maxAbsSum = 0;
    for (int i = 0; i < n; i++)
    {
        prefixSum += nums[i];

        minPrefixSum = min(minPrefixSum, prefixSum);
        maxPrefixSum = max(maxPrefixSum, prefixSum);

        // if (prefixSum >= 0)
        // {
        //     maxAbsoluteSum = max();
        // }
        // else
        // {

        // }
    }
    return maxPrefixSum - minPrefixSum;
}

int main()
{
    vector<int> nums = {2, -5, 1, -4, 3, -2};
    maxAbsoluteSum(nums);
    return 0;
}