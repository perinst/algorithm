#include <iostream>
#include <vector>
#include <stack>

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

using namespace std;

string makeFancyString(string s)
{

    string str = "";
    str += s[0];

    // stack<char> st;
    // st.push(s[0]);
    int count = 1;
    bool isFull = false;

    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] == s[i - 1] && !isFull)
        {
            str += s[i];
            isFull = true;
            continue;
        }

        if (s[i] == s[i - 1] && isFull)
        {
            continue;
        }

        isFull = false;
        str += s[i];
    }

    return str;
}

void solve()
{
    string s = "leeetcode";
    makeFancyString(s);
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