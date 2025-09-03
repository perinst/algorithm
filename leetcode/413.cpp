#include <iostream>
#include <vector>
#include <string>

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

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