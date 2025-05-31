#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int minOperations(vector<int> &nums, int k)
{
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    int step = 0;
    for (int &num : nums)
    {
        pq.push(num);
    }

    while (true)
    {
        int first = pq.top();
        pq.pop();
        if (first >= k)
        {
            break;
        }
        int second = pq.top();
        pq.pop();

        long long newNum = first * 2LL + second;
        pq.push(newNum);
        step++;
    }

    return step;
}

int main()
{
    return 0;
}