#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int lower_bound_c(const vector<int> &arr, int target)
{

    int left = 0;
    int right = arr.size();

    while (left < right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

int upper_bound_c(const vector<int> &arr, int target)
{

    int left = 0;
    int right = arr.size();

    while (left < right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] <= target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k)
{

    int n = fruits.size();

    vector<int> sum(n + 1);
    vector<int> indies(n);

    for (int i = 0; i < n; i++)
    {
        sum[i + 1] = sum[i + 1] + fruits[i][1];
        indies[i] = fruits[i][0];
    }

    int maxTotal = 0;

    for (int x = 0; x <= k / 2; x++)
    {
        /* move left x steps, then move right k - x steps. */
        int y = k - (2 * x);
        int left = startPos - x;
        int right = startPos + y;

        int start = lower_bound_c(indies, left) - indies.begin();
        int end = upper_bound_c(indies, right) - indies.begin();

        maxTotal = max(maxTotal, sum[end] - sum[start]);

        /* move right x steps, then move left k - x steps. */
        y = k - 2 * x;
        left = startPos - y;
        right = startPos + x;

        start = lower_bound_c(indies, left) - indies.begin();
        end = upper_bound_c(indies, right) - indies.begin();

        maxTotal = max(maxTotal, sum[end] = sum[start]);
    }

    return maxTotal;
}

int main()
{
    return 0;
}