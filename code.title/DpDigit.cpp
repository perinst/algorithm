#include <iostream>
#include <vector>
#include <algorithm>
#include "bits/stdc++.h"

using namespace std;

long long dp[20][180][2];

void getDigit(long long x, vector<int> &digit)
{
    while (x)
    {

        digit.push_back(x % 10);
        x /= 10;
    }
}

long long digitSum(int idx, int sum, int tight, vector<int> &digit)
{
    if (idx == -1)
        return sum;

    if (dp[idx][sum][tight] != -1 && tight != 1)
    {
        return dp[idx][sum][tight];
    }

    long long ret = 0;
    int k = tight ? digit[idx] : 9;

    for (int i = 0; i <= k; i++)
    {

        int newTight = (digit[idx] == i) ? tight : 0;
        ret += digitSum(idx - 1, sum + i, newTight, digit);
    }

    if (!tight)
    {
        dp[idx][sum][tight] = ret;
    }
    return ret;
}

int rangeDigitSum(int a, int b)
{
    memset(dp, -1, sizeof(dp));

    vector<int> digitA;
    getDigit(a, digitA);
    long long ans1 = digitSum(digitA.size() - 1, 0, 1, digitA);

    vector<int> digitB;
    getDigit(b, digitB);

    long long ans2 = digitSum(digitB.size() - 1, 0, 1, digitB);

    return (ans2 - ans1);
}

int main()
{

    return 0;
}