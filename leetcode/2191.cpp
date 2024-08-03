#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;

vector<int> sortJumbled(vector<int> &mapping, vector<int> &nums)
{

    std::unordered_map<int, int> map;

    for (int n : nums)
    {
        int original = n;
        int m = 0;
        int p = 0;

        while (n > 0)
        {
            m = m + std::pow(10, p) * mapping[n % 10];
            p++;
            n /= 10;
        }

        if (original == 0)
        {
            m = mapping[0];
        }

        map[original] = m;
    }

    sort(nums.begin(), nums.end(), [&map](int a, int b)
         {
             int mapA = map[a];
             int mapB = map[b];

             if (mapA != mapB)
                 return mapA < mapB;

            
            return a < b; });

    return nums;
}

int main()
{
    vector<int> map = {8, 9, 4, 0, 2, 1, 3, 5, 7, 6};
    vector<int> nums = {991, 338, 38};
    vector<int> rs = sortJumbled(map, nums);

    for (auto &n : rs)
    {
        cout << n << "\t";
    }

    return 1;
}