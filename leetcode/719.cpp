#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec)
{
    os << "[\n";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << "  " << vec[i];
        if (i != vec.size() - 1)
        {
            os << ",\n";
        }
    }
    os << "\n]";
    return os;
}

struct Compare
{
    bool operator()(int a, int b)
    {

        return a < b;
    }
};

int smallestDistancePair(vector<int> &nums, int k)
{
    sort(nums.begin(), nums.end());

    int n = nums.size();

    int low = 0;
    int high = nums[n - 1] - nums[0];

    while (low < high)
    {

        int mid = (low + high) / 2;

        // count distance  <= mid

        int count = countPairsWithMaxDistance(nums, mid);

        if (count < k)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

int countPairsWithMaxDistance(vector<int> &nums, int maxDistance)
{

    int cnt = 0;
    int left = 0;

    for (int right = 0; right < nums.size(); right++)
    {

        while (nums[right] - nums[left] > maxDistance)
        {
            left++;
        }

        cnt += right - left;
    }

    return cnt;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<int> nums = {1, 6, 1, 100, 3, 4};
    int k = 3;

    cout << smallestDistancePair(nums, k);

    return 0;
}