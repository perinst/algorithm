#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

bool isIsomorphic(string s, string t)
{

    unordered_map<char, char> mapSC;
    unordered_map<char, char> mapTC;

    for (int i = 0; i < s.size(); i++)
    {

        char tc = t[i];
        char sc = s[i];

        if (mapSC.find(sc) == mapSC.end())
        {
            mapSC[sc] = tc;
        }

        if (!mapTC.count(tc))
        {
            mapTC[tc] = sc;
        }

        if (mapSC[sc] != tc || mapTC[tc] != sc)
        {
            return false;
        }
    }

    return true;
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