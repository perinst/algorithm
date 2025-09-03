#include <iostream>
#include <vector>

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

vector<vector<int>> generate(int numRows)
{

    vector<vector<int>> pascals;

    for (int i = 0; i < numRows; i++)
    {

        vector<int> rows(i + 1, 1);

        if (i < 2)
        {
            pascals.push_back(rows);
            continue;
        }

        for (int j = 1; j < i; j++)
        {
            rows[j] = pascals[i - 1][j - 1] + pascals[i - 1][j];
        }

        pascals.push_back(rows);
    }

    return pascals;
}

void solve()
{
    int N;
    cin >> N;
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}