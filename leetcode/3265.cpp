#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

bool isAlmostEqual(int n1, int n2)
{

    vector<pair<int, int>> pairs;

    string str1 = to_string(n1);
    string str2 = to_string(n2);

    if (str1.size() < str2.size())
        return isAlmostEqual(n2, n1);

    while (str1.size() > str2.size())
    {
        str2 = "0" + str2;
    }

    for (int i = 0; i < str1.size(); i++)
    {
        int d1 = str1[i] - '0';
        int d2 = str2[i] - '0';

        if (d1 == d2)
            continue;
        pairs.push_back({d1, d2});
    }

    if (pairs.size() == 0)
        return true;

    if (pairs.size() != 2)
        return false;

    return pairs[0].first == pairs[1].second && pairs[1].first == pairs[0].second;
}

int countPairs(vector<int> &nums)
{
    int n = nums.size();
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {

        for (int j = i + 1; j < n; j++)
        {

            if (nums[i] == nums[j])
                cnt++;

            if (isAlmostEqual(nums[i], nums[j]))
            {
                cout << nums[i] << ", " << nums[j] << endl;
                cnt++;
            }
        }
    }

    return cnt;
}

int main()
{

    vector<int> nums = {3, 30, 12, 17, 21};
    cout << countPairs(nums);
    return 0;
}