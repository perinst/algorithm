#include <iostream>
#include <vector>
#include <string>

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
vector<int> productExceptSelf(vector<int> &nums)
{
    __int32 mul = 1;
    int a_0 = 0;

    for (int &n : nums)
    {
        if (n != 0)
            mul *= n;
        else
            a_0++;
    }

    if (a_0 > 1)
        return vector<int>(nums.size(), 0);

    if (a_0 == 1)
    {

        for (int i = 0; i < nums.size(); i++)
        {
            nums[i] = nums[i] == 0 ? nums[i] = mul : 0;
        }
        return nums;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i])
            nums[i] = mul / nums[i];
    }

    return nums;
}

vector<int> productExceptSelfPrefix(vector<int> &nums)
{
    int n = nums.size();
    vector<int> prefix(n, 1);

    int left = 1;

    for (int i = 0; i < n; i++)
    {
        prefix[i] *= left;
        left *= nums[i];
    }

    int right = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        prefix[i] *= right;
        right *= nums[i];
    }

    return prefix;
}

int main()
{
    vector<int> nums = {-1, 1, 0, -3, 3};
    cout << productExceptSelfPrefix(nums) << endl;
    return 0;
}