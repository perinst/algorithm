#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

int maxFrequencyElements(vector<int> &nums)
{
    unordered_map<int, int> freq;

    for (int n : nums)
    {
        freq[n]++;
    }

    int maxFreq = 1;

    for (int n : nums)
    {
        maxFreq = max(freq[n], maxFreq);
    }

    return maxFreq;
};

int findIndexLE(const vector<int> arr, int target)
{
    auto it = std::upper_bound(arr.begin(), arr.end(), target);

    if (it == arr.begin())
        return -1;

    return distance(arr.begin(), it - 1);
}

void preprocess(vector<int> nums, unordered_map<int, pair<int, int>> rangeMap)
{
    int n = nums.size();
    for (int i = 0; i < n;)
    {
        int val = nums[i];

        int start = i;

        while (i < n && nums[i] == val)
            i++;
        int end = i - 1;

        rangeMap[val] = {start, end};
    }
}

int maxFrequencyInRange(vector<int> nums, int L, int R)
{
    unordered_map<int, pair<int, int>> rangeMap;
    preprocess(nums, rangeMap);

    int maxFreq = 0;

    for (int i = L; i <= R;)
    {
        int val = nums[i];
        auto [start, end] = rangeMap[val];

        int freq = min(end, R) - max(start, L) + 1;
        maxFreq = max(freq, maxFreq);

        i = end + 1;
    }

    return maxFreq;
}

int maxFrequency(vector<int> &nums, int k, int numOperations)
{
    if (k == 0)
        return maxFrequencyElements(nums);

    std::sort(nums.begin(), nums.end());

    int maxFreq = 1;

    for (int i = 0; i < nums.size(); i++)
    {
        int left = nums[i] - k;
        int right = nums[i] + k;

        int l = lower_bound(nums.begin(), nums.end(), left) - nums.begin();
        int r = upper_bound(nums.begin(), nums.end(), right) - nums.begin() - 1;

        int already = upper_bound(nums.begin(), nums.end(), nums[i]) - lower_bound(nums.begin(), nums.end(), nums[i]);

        maxFreq = max(maxFreq, already + min(numOperations, (r - l + 1) - already));
    }

    return maxFreq;
}

// int maxFrequency(vector<int> &nums, int k, int numOperations)
// {

//     sort(nums.begin(), nums.end());
//     int n = nums.size();

//     int maxFreq = 0;

//     for (int i = 0; i < n; i++)
//     {
//         while (nums[right] - nums[left] > k)
//             left++ int windowSize = right - left + 1;
//         maxFreq = max(maxFreq, min(windowSize, numOperations));
//     }
//     return maxFreq;
// }

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}