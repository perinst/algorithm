#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

double are(vector<int> &a, vector<int> &b, vector<int> &c)
{
    return 0.5 * abs(a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) +
                     c[0] * (a[1] - b[1]));
}

double largestTriangleArea(vector<vector<int>> &points)
{
    double maxArea = 0.0;
    int n = points.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {

                maxArea =
                    max(maxArea, are(points[i], points[j], points[k]));
            }
        }
    }

    return maxArea;
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