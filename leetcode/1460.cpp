
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

// minimum step swap to matches arr with target

bool canBeEqual(vector<int> &target, vector<int> &arr)
{
    std::unordered_map<int, int> map;

    for (int &n : arr)
    {
        map[n]++;
    }

    for (int &n : target)
    {
        if (!map[n])
            return false;

        map[n]--;
    }
    return true;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}