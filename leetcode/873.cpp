#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>

using namespace std;

int n = 0;
int maxLen = 1;
vector<vector<int>> dp;

void maxLenFib(vector<int> &arr, vector<int> &indexFibs, int idx)
{
    maxLen = max((int)indexFibs.size(), maxLen);

    if (idx >= n)
    {
        return;
    }

    int i = indexFibs[indexFibs.size() - 1];
    int j = indexFibs[indexFibs.size() - 2];

    if (dp[i][j] > 2)
    {
        maxLen = max(dp[i][j] + 1, maxLen);
        return;
    }

    if (indexFibs.size() >= 2)
    {
        int sum = arr[i] + arr[j];
        if (arr[idx] == sum)
        {
            indexFibs.push_back(idx);
            dp[i][j] = maxLen;
        }
    }

    maxLenFib(arr, indexFibs, idx + 1);
}

int lenLongestFibSubseqV1(vector<int> &arr)
{
    n = arr.size();
    dp = vector<vector<int>>(n, vector<int>(n, 2));

    for (int i = 0; i < n - 2; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            vector<int> indexFibs = {i, j};
            maxLenFib(arr, indexFibs, j + 1);
        }
    }

    return maxLen;
}

int lenLongestFibSubseq(vector<int> &arr)
{
    unordered_set<int> set;
    int n = arr.size();
    int maxLen = 0;

    for (int start = 0; start < n - 2; start++)
    {
        for (int next = start + 1; next < n; next++)
        {
            int len = 2;
            int prev = arr[next];
            int curr = arr[next] + arr[start];

            while (set.find(curr) != set.end())
            {
                len++;
                int temp = prev;
                prev += curr;
                curr = prev + temp;
            }
            maxLen = max(maxLen, len);
        }
    }
    return maxLen;
}
int main()
{
    vector<int> arr;
    cout << lenLongestFibSubseq(arr);
    return 0;
}