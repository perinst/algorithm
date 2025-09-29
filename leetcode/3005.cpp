#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

int maxFrequencyElements(vector<int> &nums)
{
    unordered_map<int, int> freq;
    for (int n : nums)
    {
        freq[n]++;
    }

    int maxFreq = 1;

    for (int n : nums)
    {
        maxFreq = max(freq[n], maxFreq);
    }

    int total = 0;

    for (auto [key, f] : freq)
    {
        if (f == maxFreq)
            total += f;
    }

    return total;
};

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}