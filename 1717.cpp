#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

// Common typedefs
typedef long long ll;
typedef unsigned long long ull;

using namespace std;

const string AB = "ab";
const string BA = "ba";

int maximumGain(string s, int x, int y)
{

    string higherSubStr = x > y ? AB : BA;
    string lowerSubStr = higherSubStr == AB ? BA : AB;
    int higherPoint = max(x, y);
    int lowerPoint = min(x, y);

    int maxGain = 0;

    stack<char> st;

    for (char &c : s)
    {
        if (st.empty() || (string(1, st.top()) + string(1, c)) != higherSubStr)
        {
            st.push(c);
            continue;
        }

        maxGain += higherPoint;
        st.pop();
    }

    string remainStr;

    while (!st.empty())
    {
        remainStr += st.top();
        st.pop();
    }

    std::reverse(remainStr.begin(), remainStr.end());

    for (char &c : remainStr)
    {
        if (st.empty() || (string(1, st.top()) + string(1, c)) != lowerSubStr)
        {
            st.push(c);
            continue;
        }

        maxGain += lowerPoint;
        st.pop();
    }

    return maxGain;
}

void solve()
{
    string s;
    int x, y;
    cin >> s >> x >> y;

    cout << maximumGain(s, x, y) << endl;
}
int main()
{
    fast_io;

    int T = 1;
    while (T--)
    {
        solve();
    }
    return 0;
}