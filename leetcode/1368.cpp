#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<vector<int>> direction = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool isValid(int row, int col, int numRows, int numCols)
{
    return row >= 0 && row < numRows && col >= 0 && col < numCols;
}

int minCost(vector<vector<int>> &grid)
{
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> minCost(rows, vector<int>(cols, INT_MAX));
    deque<pair<int, int>> deque;
    deque.push_front({0, 0});
    minCost[0][0] = 0;

    while (!deque.empty())
    {
        auto [x, y] = deque.front();
        deque.pop_front();

        for (int d = 0; d < 4; d++)
        {
            int cost = grid[x][y] != (d + 1) ?: 0;
            int newRow = x + direction[d][0];
            int newCol = y + direction[d][1];
            if (isValid(newRow, newCol, rows, cols) && minCost[x][y] + cost < minCost[newRow][newCol])
            {

                minCost[newRow][newCol] = minCost[x][y] + cost;

                if (cost == 1)
                {
                    deque.push_back({newRow, newCol});
                }
                else
                {
                    deque.push_front({newRow, newCol});
                }
            }
        }
    }

    return minCost[rows - 1][cols - 1];
}

int main()
{
    return 0;
}
