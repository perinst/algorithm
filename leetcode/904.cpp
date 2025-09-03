#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int totalFruit(vector<int> &fruits)
{

    if (fruits.empty())
        return 0;

    int left = 0;
    int maxTotal = 1;
    unordered_map<int, int> fruitCount;

    for (int right = 0; right < fruits.size(); right++)
    {
        fruitCount[fruits[right]]++;

        while (fruitCount.size() > 2)
        {
            fruitCount[fruits[left]]--;

            if (fruitCount[fruits[left]] == 0)
            {
                fruitCount.erase(fruits[left]);
            }

            left++;
        }
        maxTotal = max(maxTotal, right - left + 1);
    }

    // while (left <= right && right < fruits.size())
    // {
    //     int totalFruits = 0;

    //     while (set.size() <= 2 && right < fruits.size())
    //     {
    //         if (set.find(fruits[right]) == set.end())
    //         {
    //             if (set.size() > 2)
    //             {
    //                 break;
    //             }
    //             else
    //             {
    //                 set.insert(fruits[right]);
    //             }
    //         }

    //         right++;
    //         totalFruits++;
    //     }

    //     maxTotal = max(maxTotal, totalFruits);

    //     left = right - 1;
    //     right = left;

    //     set.clear();
    // }

    return maxTotal;
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

    cout << totalFruit(nums) << endl;
}

int main()
{

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}