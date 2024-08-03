#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {

        vector<vector<int>> result;
        vector<int> subset;
        backtracking(0, nums, subset, result);
        return result;
    }

    void backtracking(int start, vector<int> &nums, vector<int> &subsets, vector<vector<int>> &result)
    {

        result.push_back(subsets);

        for (int i = start; i < nums.size(); ++i)
        {
            subsets.push_back(nums[i]);

            backtracking(i + 1, nums, subsets, result);

            subsets.pop_back();
        }
    }

    void printSubsets(const vector<vector<int>> &subsets)
    {
        for (const auto &subset : subsets)
        {
            cout << "[";
            for (size_t i = 0; i < subset.size(); ++i)
            {
                cout << subset[i];
                if (i < subset.size() - 1)
                    cout << ", ";
            }
            cout << "]\n";
        }
    };
};

class Monsters
{
private:
    char floor = '.';
    char wall = '#';
    char visted = 'x';
    char people = 'A';
    char monster = 'M';
    int INF = 1e9;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    char dir[4] = {'U', 'D', 'L', 'R'};

public:
    bool is_within_bounds(int x, int y, int n, int m)
    {
        return x >= 0 && y >= 0 && x < n && y < m;
    }

    void solve(int n, int m)
    {

        vector<string> maze(n);
        pair<int, int> start;
        vector<pair<int, int>> monsters;

        for (int i = 0; i < n; ++i)
        {

            for (int j = 0; j < m; ++j)
            {
                cin >> maze[i][j];
                if (maze[i][j] == 'A')
                {
                    start = {i, j};
                }
                else if (maze[i][j] == 'M')
                {
                    monsters.push_back({i, j});
                }
            }
        }

        vector<vector<int>> monster_dist(n, vector<int>(m, INF));
        queue<pair<int, int>> q;

        for (auto &[mx, my] : monsters)
        {
            q.push({mx, my});
            monster_dist[mx][my] = 0;
        }

        while (!q.empty())
        {

            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++)
            {

                int nx = x + dx[d];
                int ny = y + dy[d];

                if (is_within_bounds(nx, ny, n, m) && maze[nx][ny] == floor && monster_dist[nx][ny] == INF)
                {
                    monster_dist[nx][ny]++;
                    q.push({nx, ny});
                }
            }
        }

        vector<vector<int>> player_dist(n, vector<int>(m, INF));
        vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));

        player_dist[start.first][start.second] = 0;

        q.push(start);

        pair<int, int> exit = {-1, -1};

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            if (x == 0 || x == n - 1 || y == 0 || y == m - 1)
            {
                exit = {x, y};
                break;
            }

            for (int d = 0; d < 4; d++)
            {

                int nx = x + dx[d];
                int ny = y + dy[d];

                if (is_within_bounds(nx, ny, n, m) && maze[nx][ny] == floor && player_dist[nx][ny] == INF)
                {

                    // !!!!!!
                    if (player_dist[nx][ny] + 1 < monster_dist[nx][ny])
                    {
                        parent[nx][ny] = {x, y};
                        player_dist[nx][ny]++;
                        q.push({nx, ny});
                    }
                }
            }
        }

        if (exit.first == -1 && exit.second == -1)
        {
            cout << "No";
            return;
        }

        cout << "Yes\n";
        pair<int, int> cur = exit;
        string path;

        while (cur != start)
        {
            auto [x, y] = parent[cur.first][cur.second];

            for (int d = 0; d < 4; d++)
            {

                if (x + dx[d] == cur.first && y + dy[d] == cur.second)
                {
                    path += dir[d];
                    break;
                }
            }

            cur = parent[cur.first][cur.second];
        }

        reverse(path.begin(), path.end());
        cout << path.size() << '\n';
        cout << path << '\n';
    }
    // bool stepWalk(vector<vector<char>> &m, int i, int j, int step, vector<string> path)
    // {

    //     if (m[i][j] == visted || m[i][j] == wall || i < 0 || j < 0 || i >= m.size() || j >= m[0].size())
    //         return false;

    //     char temp = m[i][j];
    //     m[i][j] = visted;

    //     stepWalk(m; i + 1; j; step++; path + 'D');
    //     stepWalk(m; i - 1; j; step++; path + "U");
    //     stepWalk(m; i; j + 1; step++; path + "R");
    //     stepWalk(m; i; j - 1; step++; path + "L");
    //     //
    //     m[i][j] = temp;
    //     //
    //     return true;
    // }

    // void wayForUser()
    // {
    // }

    // void wayForMonster()
    // {
    // }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Monsters mon;
    mon.solve(n, m);
}