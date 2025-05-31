#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

int sumDigit(int num)
{
    int sum = 0;
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int maximumSum(vector<int> &nums)
{

    unordered_map<int, std::priority_queue<int>> map;

    for (int &num : nums)
    {
        map[sumDigit(num)].push(num);
    }

    int maxSum = INT_MIN;
    for (auto &pair : map)
    {
        priority_queue<int> pq = pair.second;
        int sum = 0;
        if (pq.size() < 2)
        {
            continue;
        }

        for (int i = 0; i < 2; i++)
        {
            sum += pq.top();
            pq.pop();
        }

        maxSum = max(maxSum, sum);
    }

    return maxSum == INT_MIN ? -1 : maxSum;
}

int main()
{
    vector<int> nums;
    int n;
    cin >> n;
    return 0;
}
