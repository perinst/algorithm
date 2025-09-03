
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

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

const int maxN = 110;

int r, c;
char a[maxN][maxN];
int d[maxN][maxN];
bool visit[maxN][maxN];
int moveX[] = {0, 0, 1, -1};
int moveY[] = {1, -1, 0, 0};

void bfs(int sx, int sy)
{
    for (int i = 1; i <= r; ++i)
    {
        fill_n(d[i], c + 1, 0);
        fill_n(visit[i], c + 1, false);
    }

    queue<pair<int, int>> q;
    q.push({sx, sy});
    visit[sx][sy] = true;

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // Nếu gặp được ô B thì kết thúc thủ tục BFS
        if (a[x][y] == 'B')
        {
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            int u = x + moveX[i];
            int v = y + moveY[i];

            if (u > r || u < 1)
                continue;
            if (v > c || v < 1)
                continue;
            if (a[u][v] == '*')
                continue;

            if (!visit[u][v])
            {
                d[u][v] = d[x][y] + 1;
                visit[u][v] = true;
                q.push({u, v});
            }
        }
    }
}

int dp[maxN][maxN];

// Relaxation nhiều lần
int solveDP(int sx, int sy, int tx, int ty)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < = m; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }

    dp[sx][sy] = 0;

    for (int tier = 0; tier < r * c; tier++)
    {
        bool updated = false;
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j < = j; j++)
            {
                if (a[i][j] == "*" || dp[i][j] == INT_MAX)
                    continue;

                for (int k = 0; k < 4; k++ i)
                {
                    int ni = i + moveX[k];
                    int nj = i + moveY[k];

                    if (ni < 1 || nj < 1 || ni > r || nj > c)
                        continue;

                    if (dp[i][j] + 1 < dp[ni][nj])
                    {
                        dp[ni][nj] = dp[i][j] + 1;
                        updated = true;
                    }
                }
            }
        }
        if (!updated)
            break;
    }

    return dp[tx][ty];
}

void solve()
{
    int sx, sy, tx, ty;
    cin >> r >> c;
    for (int i = 1; i <= r; ++i)
        for (int j = 1; j <= c; ++j)
        {
            cin >> a[i][j];
            if (a[i][j] == 'C')
            {
                sx = i;
                sy = j;
            }
            if (a[i][j] == 'B')
            {
                tx = i;
                ty = j;
            }
        }

    bfs(sx, sy);
    cout << d[tx][ty];
}

int main()
{
    fast_io;

    int t = 1;
    // cin >> t; // Uncomment for multiple test cases

    while (t--)
    {
        solve();
    }

    return 0;
}