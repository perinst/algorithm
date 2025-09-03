#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <numeric>
#include <iomanip>

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < sz(v); i++)
    {
        os << v[i];
        if (i != sz(v) - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

int maximumUniqueSubarray(vector<int> &nums)
{

    vector<int> slides(nums.size() + 1);
    unordered_map<int, int> mapIndex;

    int maxSum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        slides[i + 1] = slides[i] + nums[i];
    }

    int left = 0;

    for (int right = 0; right < nums.size(); right++)
    {
        if (mapIndex.count(nums[right]) && mapIndex[nums[right]] >= left)
        {
            int currentSum = slides[right] - slides[left];
            maxSum = max(currentSum, maxSum);
            left = mapIndex[nums[right]] + 1;
        }

        mapIndex[nums[right]] = right;
    }

    int sumSlice = slides[nums.size()] - slides[left];

    maxSum = max(maxSum, sumSlice);

    return maxSum;
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

    cout << maximumUniqueSubarray(nums) << endl;
}
int main()
{
    fast_io;

    int T = 1;
    while (T--)
    {
        solve();
    }

    return 0;
}