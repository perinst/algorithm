#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long maximumTripletValue(vector<int> &nums)
{
    const int n = nums.size();
    vector<int> prefixMath(n, 0);
    vector<int> suffixMax(n, 0);

    prefixMath[0] = nums[0];
    suffixMax[n - 1] = nums[n - 1];

    for (int i = 1; i < n; i++)
    {
        prefixMath[i] = max(prefixMath[i - 1], nums[i]);
        suffixMax[n - i - 1] = max(suffixMax[n - i], nums[n - i - 1]);
    }

    long long maxTriple = 0;

    for (int i = 1; i < n - 1; i++)
    {
        long long cal = (long long)(prefixMath[i - 1] - nums[i]) * suffixMax[i + 1];
        maxTriple = max(maxTriple, cal);
    }

    return maxTriple;
}

int main()
{
    vector<int> nums = {2, 3, 1};
    cout << maximumTripletValue(nums);
    return 0;
}