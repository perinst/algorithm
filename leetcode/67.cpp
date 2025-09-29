#include <iostream>
#include <vector>
#include <string>

using namespace std;

string addBinary(string a, string b)
{
    int cary = 0;
    int i = max(a.size(), b.size());
    int numA = std::stoi(a);
    int numB = std::stoi(b);
    string rs = "";

    while (i--)
    {
        int digitNumA = numA % 10;
        int digitNumB = numB % 10;
        numA /= 10;
        numB /= 10;

        if (digitNumA != digitNumB)
        {
            rs = "1" + rs;
            cary = 0;
            continue;
        }

        if (cary)
        {
            rs = "1" + rs;
            cary = 0;
        }
        else
        {
            rs = "0" + rs;
        }

        cary = digitNumA;
    }

    if (cary > 0)
    {
        rs = "1" + rs;
    }

    return rs;
}

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

void solve()
{
    string a = "1111";
    string b = "1111";

    cout << addBinary(a, b);
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