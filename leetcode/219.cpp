#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

bool containsNearbyDuplicate(vector<int> &nums, int k)
{
    unordered_map<int, int> hMap;

    for (int i = 0; i < nums.size(); i++)
    {
        if (hMap.find(nums[i]) == hMap.end())
        {
            hMap[nums[i]] = i;
            continue;
        }

        int j = hMap[nums[i]];

        if (abs(i - j) <= k)
        {
            return true;
        }
        else
        {
            hMap[nums[i]] = j
        }
    }

    return false;
}

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}