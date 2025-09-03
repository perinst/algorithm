#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
{

    for (int &fruit : fruits)
    {

        for (int i = 0; i < baskets.size(); i++)
        {
            int basket = baskets[i];

            if (basket >= fruit)
            {
                baskets.erase(baskets.begin() + i);
                break;
            }
        }
    }

    return baskets.size();
}

void solve()
{
    int N;
    cin >> N;
    vector<int> fruits(N);
    vector<int> baskets(N);
    for (int i = 0; i < N; i++)
    {
        cin >> fruits[i];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> baskets[i];
    }

    cout << numOfUnplacedFruits(fruits, baskets) << endl;
}

int main()
{

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}