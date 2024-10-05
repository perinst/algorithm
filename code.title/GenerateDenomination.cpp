#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
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

using namespace std;

unordered_set<int> memo;
int n;
vector<int> money;

void backtracking(vector<int> &prices, int idx, int &p)
{

    if (memo.find(p) == memo.end())
        money.emplace_back(p);
    else
    {
        memo.insert(p);
    }

    for (int i = idx; i < n; i++)
    {
        p += prices[i];

        backtracking(prices, i + 1, p);

        p -= prices[i];
    }
}

vector<int> solve(vector<int> &prices)
{
    std::sort(prices.begin(), prices.end());
    int p = 0;
    backtracking(prices, 0, prices[0]);
    return money;
}

int main()
{
    int n;
    cin >> n;
    vector<int> denominations(n);

    for (int i = 0; i < n; i++)
    {
        cin >> denominations[i];
    }

    cout << solve(denominations);

    return 0;
}