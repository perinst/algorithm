#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
int N;
int M;

bool outside(int i, int j)
{
    return i < 0 || i >= N || j < 0 || j >= M;
}

bool bfs(vector<vector<int>> &grid1, vector<vector<int>> &grid2, int i, int j)
{

    if (i < 0 || j < 0 || i >= N || j >= M || grid2[i][j] == 0)
    {
        return true;
    }

    if (grid1[i][j] != 1)
    {
        return false;
    }

    // Mark the cell in grid2 as visited
    grid2[i][j] = 0;
    grid2[i][j] = 0;

    return bfs(grid1, grid2, i + 1, j) && bfs(grid1, grid2, i - 1, j) && bfs(grid1, grid2, i, j + 1) && bfs(grid1, grid2, i, j - 1);
}

int countSubIslands(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
{
    N = grid1.size();
    M = grid1[0].size();

    int ans = 0;

    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < M; j++)
        {
            if (!grid2[i][j])
                continue;

            if (!grid1[i][j])
                continue;

            if (bfs(grid1, grid2, i, j))
                ans++;
        }
    }
    return ans;
}

int main()
{
    return 0;
}