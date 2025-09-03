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

using namespace std;
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

void solve()
{

    // cout << "Result: " << fib(5) << endl;
}

long long kthSmallestProduct(vector<int> &nums1, vector<int> &nums2, long long k)
{
    long long smallest = 0;
    int n1_left = 0, n2_left = 0;
    int n1_right = nums1.size() - 1, n2_right = nums2.size() - 1;

    while (k > 0 && (n1_left < n1_right) && (n2_left < n2_right))
    {
        int minValue = min(nums1[n1_left], nums2[n2_left]);

        int min_1 = min(nums1[n1_left] * nums2[n2_right], nums1[n1_left] * nums2[n2_left]);

        int min_2 = min(nums2[n2_left] * nums1[n1_right], nums2[n2_left] * nums1[n1_left]);

        if (min_1 < min_2)
        {
            if (nums1[n1_left] < 0)
            {
                n2_right--;
            }
            else
            {
                n2_left++;
            }
        }
        else
        {
            if (nums2[n2_left] < 0)
            {
                n1_right--;
            }
            else
            {
                n1_left++;
            }
        }

        smallest = min(min_1, min_2);
        k--;
    }

    cout << n1_left << n1_right << n2_left << n2_right << endl;

    return smallest;
}

int main()
{
    fast_io;

    int T = 1;
    cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}