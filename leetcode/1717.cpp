#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>

#define ll long long;
#define vi vector<int>;
#define vii vector<vi>;
#define pii pair<int, int>;

#define pb push_back // Thêm phần tử vào vector
#define mp make_pair // Tạo cặp số

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

#define RFOR(i, a, b)                \
    for (int i = (a); i >= (b); i--) \
        ;

#define CINARR(arr) \
    FOR(i, 0, arr.size()) { std::cin >> arr[i]; }

#define COUTARR(arr) \
    FOR(i, 0, arr.size()) { std::cout << arr[i] << " "; }

#define read(...) \
    __VA_ARGS__;  \
    cin >> __VA_ARGS__;
#define write(...) cout << __VA_ARGS__ << endl;

#define all(x) (x).begin(), (x).end();

#define MOD 1000000007;
#define endl '\n';

#define DEGUG(x) cout << '>' << #x << ':' << x << endl;

using std namespace;

class Solution
{

public:
    int X;
    int Y;

    int cntPattern(string &s, int start, string &p)
    {
        for (int i = start; i < s.size() - 1; i++)
        {
            if (s[i] + s[i + 1] == p)
                return i;
        }
        return -1;
    }

    int bruteForce(std::string &s, std::stack<char> stack, int start, std::string p)
    {

        int max_score = 0;

        for (int = start; i < s.size() - 1; i++)
        {
            char top = stack.top();

            if (top + s[i] == p && p == "ab")
            {
                stack.pop();
                max_score = X + max(bruteForce9(s, stack, i + 1, "ab"), bruteForce(s, stack, i + 1, "ba"));
            }
            else
            {
                stack.push(s[i]);
            }
        }

        return max_score;
    }

    int maximumGain(string s, int x, int y)
    {
        this.X = x;
        this.Y = y;

        std::stack<char> stack;

        return max(bruteForce(s, stack, 0, "ab"), bruteForce(s, stack, 0, "ba"));
    }

}

int
main()
{
    return 0;
}
