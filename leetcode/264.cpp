#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_set>

using namespace std;

int nthUglyNumber(int n)
{

    std::set<long> set;
    set.insert(1);

    long currUgly = 1;

    for (int i = 0; i <= n; i++)
    {
        currUgly = *set.begin();
        set.erase(*set.begin());

        set.insert(currUgly * 2);
        set.insert(currUgly * 3);
        set.insert(currUgly * 5);
    }

    return static_cast<int>(currUgly);
}

int nthUglyNumberMinHeap(int n)
{
    unordered_set<long> set;
    vector<int> primes = {2, 3, 5};
    std::priority_queue<long, vector<long>, greater<long>> minHeap;

    minHeap.push(1);
    long currUgly = 1;

    for (int i = 0; i < n; i++)
    {
        currUgly = minHeap.top();
        minHeap.pop();

        for (int &p : primes)
        {
            long next = currUgly * p;
            if (set.find(next) == set.end())
            {
                minHeap.push(next);
                set.insert(next);
            }
        }
    }
    return currUgly;
}

int nthUglyNumberDp(int n)
{
    vector<int> dp(n);
    dp[0] = 1;

    // Three pointers for the multiples of 2, 3, and 5

    int indexMultipleOf2 = 0, indexMultipleOf3 = 0, indexMultipleOf5 = 0;
    int nextMultipleOf2 = 2, nextMultipleOf3 = 3, nextMultipleOf5 = 5;

    for (int i = 1; i < n; i++)
    {

        int nextUglyNumber = min(nextMultipleOf2, min(nextMultipleOf3, nextMultipleOf5));
        dp[i] = nextUglyNumber;

        //
        if (nextUglyNumber == nextMultipleOf2)
        {
            indexMultipleOf2++;
            nextMultipleOf2 = dp[indexMultipleOf2] * 2;
        }

        if (nextUglyNumber == nextMultipleOf3)
        {
            indexMultipleOf3++;
            nextMultipleOf3 = dp[indexMultipleOf3] * 3;
        }

        if (nextMultipleOf5 == nextUglyNumber)
        {
            indexMultipleOf5++;
            nextMultipleOf5 = dp[indexMultipleOf5] * 5;
        }
    }

    return dp[n - 1];
}

int main()
{
    nthUglyNumber(10);

    return 0;
}