#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

pair<double, double> linerRegression(vector<vector<int>> points)
{
    int n = points.size();

    double sumX = 0.0, sumY = 0.0;

    for (const auto &p : points)
    {
        sumX += p[0];
        sumY += p[1];
    }

    double meanX = sumX / n;
    double meanY = sumY / n;

    double numerator = 0, denominator = 0;

    for (auto &p : points)
    {
        numerator += (p[0] - meanX) * (p[1] - meanY);
        denominator += (p[0] - meanX) * (p[0] - meanX);
    }

    int a = numerator / denominator;
    double b = meanY - a * meanX;

    return {a, b};
}

void solve()
{
    int N;
    cin >> N;
    vector<vector<int>> points(N);

    for (int i = 0; i < N; i++)
    {
        double x, y;
        cin >> x >> y;

        points.push_back({x, y});
    }

    vector<vector<int>> ps = {{1, 1},
                              {2, 2},
                              {2, 4}};

    auto [a, b] = linerRegression(points);

    cout << "PT : y= " << a << "x + " << b << endl;

    double t = 4;
    double predY = a * t + b;

    cout << "prd" << predY << endl;
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