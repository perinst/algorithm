#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool isDistinctNumber(vector<vector<int>> &grid, int i, int j)
{

    vector<bool> isExist(9, false);

    for (int k = i; k < 3; k++)
    {
        for (int d = j; d < 3; d++)
        {
            if (isExist[grid[k][d]] || grid[d][k] > 9 || grid[d][k] < 1)
                return false;
            isExist[grid[k][d]] = true;
        }
    }

        return true;
}

int numMagicSquaresInside(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {

        if (i + 2 >= n)
            continue;

        for (int j = 0; j < m; j++)
        {

            if (j + 2 >= m)
                continue;

            if (!isDistinctNumber(grid, i, j))
                continue;

            int target = grid[i][0] + grid[i][1] + grid[i][2];

            if (grid[i][j] + grid[i + 2][j + 2] !=
                grid[i][j + 2] + grid[i + 2][j])
                continue;

            if (grid[i][j + 1] + grid[i + 2][j + 1] !=
                grid[i + 1][j] + grid[i + 1][j + 2])
                continue;

            bool isValidRowCol = true;

            for (int k = 0; k < 3; k++)
            {

                int sCol = grid[i + k][j] + grid[i + k][j + 1] +
                           grid[i + k][j + 2];

                int sRow = grid[i][j + k] + grid[i + 1][j + k] +
                           grid[i + 2][j + k];

                if (sRow != target || sCol != target)
                {
                    isValidRowCol = false;
                    break;
                }
            }

            if (!isValidRowCol)
                continue;
            bool isValidCol = true;

            cnt++;
            //
        }
    }

    return cnt;
}

int main()
{
    return 0;
}