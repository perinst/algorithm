#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <numeric>
#include <iomanip>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

// Common typedefs
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<string> vs;
typedef vector<pii> vpii;

// Common constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const double EPS = 1e-9;

// Utility macros
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

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

// Debug template
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < sz(v); i++)
    {
        os << v[i];
        if (i != sz(v) - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

// ========== RECURSION DEBUG UTILITIES ==========

#define DEBUG true

int depth = 0;

// Print function entry with parameters
#define REC_ENTER(func_name, ...)                                    \
    if (DEBUG)                                                       \
    {                                                                \
        cout << string(depth * 2, ' ') << "-> " << func_name << "("; \
        print_params(__VA_ARGS__);                                   \
        cout << ")" << endl;                                         \
        depth++;                                                     \
    }

#define REC_EXIT(func_name, result)                                                      \
    if (DEBUG)                                                                           \
    {                                                                                    \
        depth--;                                                                         \
        cout << string(depth * 2, ' ') << "<- " << func_name << " = " << result << endl; \
    }

// Print memo hit
#define MEMO_HIT(key, value)                                                                  \
    if (DEBUG)                                                                                \
    {                                                                                         \
        cout << string(depth * 2, ' ') << "   [MEMO HIT] " << key << " -> " << value << endl; \
    }

// Print memo store
#define MEMO_STORE(key, value)                                                                  \
    if (DEBUG)                                                                                  \
    {                                                                                           \
        cout << string(depth * 2, ' ') << "   [MEMO STORE] " << key << " -> " << value << endl; \
    }

// Helper to print parameters
template <typename T>
void print_params(T &&t)
{
    cout << t;
}

template <typename T, typename... Args>
void print_params(T &&t, Args &&...args)
{
    cout << t << ", ";
    print_params(args...);
}

// map<int, int> memo;

// Example usage:
// int fib(int n)
// {
//     REC_ENTER("fib", n);

//     if (memo.count(n))
//     {
//         MEMO_HIT(n, memo[n]);
//         REC_EXIT("fib", memo[n]);
//         return memo[n];
//     }

//     if (n <= 1)
//     {
//         memo[n] = n;
//         MEMO_STORE(n, n);
//         REC_EXIT("fib", n);
//         return n;
//     }

//     int result = fib(n - 1) + fib(n - 2);
//     memo[n] = result;
//     MEMO_STORE(n, result);
//     REC_EXIT("fib", result);
//     return result;
// }

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
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