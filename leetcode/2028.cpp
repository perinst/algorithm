#include <iostream>
#include <vector>

using namespace std;
vector<int> missingRolls(vector<int> &rolls, int mean, int n)
{
    int sm = 0;
    int m = rolls.size();

    for (int &r : rolls)
    {
        sm += r;
    }

    int sn = mean * (m + n) - sm;

    if (sn > 6 * n || sn < n)
        return {};

    int average = sn / n;

    vector<int> o(n);

    while (n--)
    {
        o[n] = average;
        sn -= average;
        if (n > 0)
        {
            average = sn / n;
        }
    }

    return o;
}

int main()
{
    return 0;
}
