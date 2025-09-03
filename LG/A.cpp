#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

double calMyTime(int X, int Z, int mySpeed)
{
    if (Z >= X)
    {
        return (double)Z / X;
    }
    return 1.0 + (double)(X - Z) / mySpeed;
}

int solve()
{
    int N, X, Y;
    cin >> N >> X >> Y;

    vector<int> V(N);

    for (int i = 0; i < N; i++)
    {
        cin >> V[i];
    }

    double minOpponentTime = (double)X / V[0];

    for (int i = 1; i < N - 1; i++)
    {
        double time = (double)X / V[i];
        minOpponentTime = min(minOpponentTime, time);
    }

    int mySpeed = V[N - 1];
    double myTimeWithoutBoost = (double)X / mySpeed;

    if (myTimeWithoutBoost < minOpponentTime)
        return 0;

    int maxSpeed = *max_element(V.begin(), V.end());

    double myTimeWithMaxBooster = calMyTime(X, Y, mySpeed);

    if (myTimeWithMaxBooster >= minOpponentTime)
        return -1;

    int l = 1,
        r = Y;
    int ans = Y;

    while (l <= r)
    {
        int mid = (r + l) / 2;
        double myTime = calMyTime(X, mid, mySpeed);

        if (myTime < minOpponentTime)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

int main()
{
    fast_io;

    int T = 1;
    cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}