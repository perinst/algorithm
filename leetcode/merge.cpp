#include <iostream>
#include <cmath>

#include <string>

#include <vector>

using namespace std;

vector<int> merge(vector<int> &nums)
{
    if (nums.size() == 1)
        return nums;

    int mid = (right + left) / 2;
    std::vector<int> leftSub(mid - left - 1);
    std::vector<int> rightSub(right - mid);

    for (int i = left; i < mid; i++)
    {
        leftSub[i] = nums[i];
    }

    for (int i = mid + 1; i < right; i++)
    {
        rightSub[i] = nums[i];
    }

    vector<int> rs;

    int i = 0, j = 0;
    while (i < leftSub.size() && j < rightSub.size())
    {
        if (leftSub[i] < rightSub[j])
        {
            rs.push_back(leftSub[i]);
            i++;
        }
        else
        {
            rs.push_back(rightSub[j]);
            j++;
        }
    }

    while (i < leftSub.size())
    {
        rs.push_back(leftSub[i]);
        i++;
    }

    while (j < rightSub.size())
    {
        rs.push_back(rightSub[j]);
        j++;
    }
    return rs;
}

vector<int> merge_sort(vector<int> &nums)
{

    if (nums.size() > 1)
    {
        int left = 0, right = nums.size();
        int mid = (right + left) / 2;
        merge(nums, left, mid);
        merge(nums, mid + 1, right);
    }
}

int main()
{

    return 0;
}