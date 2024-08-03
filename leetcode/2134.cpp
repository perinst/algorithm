#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// time limit execute
int minSwaps(vector<int> &nums)
{
    int op1 = minSwapsHelper(nums, 0); // Grouping all 0s together
    int op2 = minSwapsHelper(nums, 1); // Grouping all 1s together
    return min(op1, op2);
}

int minSwapsHelper(const vector<int> &data, int val)
{
    int length = data.size();
    vector<int> rightSuffixSum(length + 1, 0);

    // Construct the suffix sum array for counting opposite values
    // (val ^ 1)
    for (int i = length - 1; i >= 0; i--)
    {
        rightSuffixSum[i] = rightSuffixSum[i + 1];
        if (data[i] == (val ^ 1))
            rightSuffixSum[i]++;
    }

    // Total zeros in the array if `val` is 1 (or vice versa)
    int totalSwapsNeeded = rightSuffixSum[0];
    // Track current number of required swaps in the current segment
    int currentSwapCount = 0;
    int minimumSwaps =
        totalSwapsNeeded - rightSuffixSum[length - totalSwapsNeeded];

    // Iterate to find the minimum swaps by sliding the potential block of
    // grouped `val`
    for (int i = 0; i < totalSwapsNeeded; i++)
    {
        if (data[i] == (val ^ 1))
            currentSwapCount++;
        int remaining = (totalSwapsNeeded - i - 1);
        int requiredSwaps =
            ((i + 1) - currentSwapCount) +
            (remaining - rightSuffixSum[length - remaining]);
        minimumSwaps = min(minimumSwaps, requiredSwaps);
    }
    return minimumSwaps;
}

int minSwaps(vector<int> &nums)
{
    int amount_1 = 0;

    for (int &n : nums)
    {
        if (n == 1)
            amount_1++;
    }

    if (amount_1 == 0)
        return 0;

    int start = 0;
    int end = amount_1 - 1;

    int min_a_0 = 0;

    for (int i = start; i <= end; i++)
    {
        if (nums[i] == 0)
        {
            min_a_0++;
        }
    }
    int current_a_0 = min_a_0;

    while (start < nums.size())
    {

        int nextIdx = (end + 1) % nums.size();

        if (nums[nextIdx] != nums[start])
        {
            current_a_0 = nums[nextIdx] == 1 ? current_a_0 - 1 : current_a_0 + 1;
        }

        min_a_0 = min(min_a_0, current_a_0);

        start++;
        end = nextIdx;
    }

    return min_a_0;
}

int main()
{
    vector<int> t = {1, 1, 1, 0, 0, 1, 0, 1, 1, 0};
    cout << minSwaps(t);
    return 0;
}
static const int fast = []
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    return 0;
}();