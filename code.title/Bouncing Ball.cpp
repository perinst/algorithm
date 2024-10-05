
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
const int direction_r = 1;
const int direction_l = -1;

int isDestroyedAll(vector<int> &a, int idx, char direction)
{

    long long sRight = 0;
    long long sLeft = 0;

    for (int i = idx; i < a.size(); i++)
    {
        sRight += a[i];
    }

    for (int i = idx; i >= 0; i--)
    {
        sLeft += a[i];
    }

    if (sRight == sLeft)
        return 1;

    if (direction == 'r' && sRight - sLeft == 1)
        return 1;

    if (direction == 'l' && sLeft - sRight == 1)
        return 1;

    return 0;
}

int solve()
{

    int n;
    cin >> n;
    vector<int> a(n);
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] != 0)
            continue;
        if (isDestroyedAll(a, i, 'r'))
            cnt++;
        if (isDestroyedAll(a, i, 'l'))
            cnt++;
    }
    return cnt;
}

void runTest(int T)
{
    while (T--)
    {
        cout << solve() << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    runTest(T);
}
