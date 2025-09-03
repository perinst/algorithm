#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

int divide(string &s, int &k, int left, int right)
{

    if (right - left + 1 < k)
        return 0;

    unordered_map<char, int> freq;

    for (char &c : s)
    {
        freq[c]++;
    }

    for (int i = left; i <= right; i++)
    {

        if (freq[i] >= k)
            continue;

        int newLeft = i + 1;

        while (newLeft <= right && fre[s[newLeft]] < k)
        {
            newLeft++;
        }

        return max(divide(s, k, left, i - 1), divide(s, k, newLeft, right));
    }

    return right - left + 1;
}

int longestSubstring(string s, int k)
{
    return divide(s, k, 0, s.size() - 1);
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
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}