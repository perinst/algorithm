#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

vector<int> dp;

int maxValue(vector<pair<int, int>> &T, int remainW, int idx)
{
    if (remainW == 0)
        return 0;
    if (dp[remainW] != -1)
        return dp[remainW];

    int smax = 0;

    for (int i = idx; i < T.size(); i++)
    {
        if (T[i].first > remainW)
            continue;

        int value = T[i].second + maxValue(T, remainW - T[i].first, i);
        smax = max(smax, value);
    }

    return dp[remainW] = smax;
}

int solve(long &W, int &N, vector<int> &A, vector<int> &C)
{

    vector<pair<int, int>> T(N);
    dp.resize(N + 1, -1);

    for (int i = 0; i < N; i++)
    {
        T[i] = {A[i], C[i]};
    }

    // std::sort(T.begin(), T.end(), greater<int>());

    return maxValue(T, W, 0);
}

int main()
{
    long W;
    int N;

    cin >> W >> N;

    vector<int> A(N);
    vector<int> C(N);

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }

    cout << solve(W, N, A, C);

    return 0;
}