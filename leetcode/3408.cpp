#include <iostream>
#include <vector>
#include <string>

using namespace std;
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
// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class TaskManager
{
public:
    TaskManager(vector<vector<int>> &tasks)
    {
    }

    void add(int userId, int taskId, int priority)
    {
    }

    void edit(int taskId, int newPriority)
    {
    }

    void rmv(int taskId)
    {
    }

    int execTop()
    {
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */

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